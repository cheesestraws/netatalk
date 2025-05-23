/*
 * Copyright (c) 1990,1993 Regents of The University of Michigan.
 * All Rights Reserved.  See COPYRIGHT.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include <arpa/inet.h>
#include <ctype.h>
#include <fcntl.h>

#ifdef HAVE_KERBEROS
#ifdef HAVE_KRB5_KRB5_H
#include <krb5/krb5.h>
#else
#include <krb5.h>
#endif /* HAVE_KRB5_KRB5_H */
#endif /* HAVE_KERBEROS */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include <atalk/dsi.h>
#include <atalk/atp.h>
#include <atalk/asp.h>
#include <atalk/globals.h>
#include <atalk/logger.h>
#include <atalk/unicode.h>
#include <atalk/util.h>

#include "afp_config.h"
#include "icon.h"
#include "status.h"
#include "uam_auth.h"

static   size_t maxstatuslen = 0;

static int uam_gss_enabled(void)
{
    /* XXX: must be a better way to find out if uam_gss is active */
    return auth_uamfind(UAM_SERVER_LOGIN_EXT,
                        "Client Krb v2",
                        sizeof("Client Krb v2")) != NULL;
}

static void status_flags(char *data,
                         const int notif,
                         const int ipok,
                         const unsigned char passwdbits,
                         const int dirsrvcs,
                         int flags)
{
    uint16_t           status;
    status = AFPSRVRINFO_COPY
             | AFPSRVRINFO_SRVSIGNATURE
             | AFPSRVRINFO_SRVMSGS
             | AFPSRVRINFO_FASTBOZO
             | AFPSRVRINFO_SRVUTF8
             | AFPSRVRINFO_EXTSLEEP;

    /* some uams may not allow this. */
    if (passwdbits & PASSWD_SET) {
        status |= AFPSRVRINFO_PASSWD;
    }

    if (passwdbits & PASSWD_NOSAVE) {
        status |= AFPSRVRINFO_NOSAVEPASSWD;
    }

    /* only advertise tcp/ip if we have a valid address */
    if (ipok) {
        status |= AFPSRVRINFO_TCPIP;
    }

    /* Default is yes */
    if (notif) {
        status |= AFPSRVRINFO_SRVNOTIFY;
    }

    if (dirsrvcs) {
        status |= AFPSRVRINFO_SRVRDIR;
    }

    if (flags & OPTION_UUID) {
        status |= AFPSRVRINFO_UUID;
    }

    status = htons(status);
    memcpy(data + AFPSTATUS_FLAGOFF, &status, sizeof(status));
}

static int status_server(char *data, const char *server,
                         const struct afp_options *options)
{
    char                *start = data;
    char       *Obj;
    char		buf[32];
    uint16_t           status;
    size_t		len;
    /* make room for all offsets before server name */
    data += AFPSTATUS_PRELEN;
    /* extract the obj part of the server */
    Obj = (char *) server;

    if ((size_t) -1 == (len = convert_string(
                                  options->unixcharset, options->maccharset,
                                  Obj, -1, buf, sizeof(buf)))) {
        len = MIN(strlen(Obj), 31);
        *data++ = len;
        memcpy(data, Obj, len);
        LOG(log_error, logtype_afpd, "Could not set servername, using fallback");
    } else {
        *data++ = len;
        memcpy(data, buf, len);
    }

    /* pad server name and length byte to even boundary */
    if ((len + 1) & 1) {
        len++;
    }

    data += len;
    /* make room for signature and net address offset. save location of
     * signature offset. we're also making room for directory names offset
     * and the utf-8 server name offset.
     *
     * NOTE: technically, we don't need to reserve space for the
     * signature and net address offsets if they're not going to be
     * used. as there are no offsets after them, it doesn't hurt to
     * have them specified though. so, we just do that to simplify
     * things.
     *
     * NOTE2: AFP3.1 Documentation states that the directory names offset
     * is a required feature, even though it can be set to zero.
     */
    len = data - start;
    status = htons(len + AFPSTATUS_POSTLEN);
    memcpy(start + AFPSTATUS_MACHOFF, &status, sizeof(status));
    return len; /* return the offset to beginning of signature offset */
}

static void status_machine(char *data)
{
    char                *start = data;
    uint16_t           status;
    int			len;
    const char		*machine = "Netatalk%s";
    char buf[AFPSTATUS_MACHLEN + 1];
    memcpy(&status, start + AFPSTATUS_MACHOFF, sizeof(status));
    data += ntohs(status);

    if ((strlen(machine) + strlen(VERSION)) <= AFPSTATUS_MACHLEN) {
        len = snprintf(buf, AFPSTATUS_MACHLEN + 1, machine, VERSION);
    } else {
        if (strlen(VERSION) > AFPSTATUS_MACHLEN) {
            len = snprintf(buf, AFPSTATUS_MACHLEN + 1, VERSION);
        } else {
            (void)snprintf(buf, AFPSTATUS_MACHLEN + 1, machine, "");
            (void)snprintf(buf + AFPSTATUS_MACHLEN - strlen(VERSION),
                           strlen(VERSION) + 1,
                           VERSION);
            len = AFPSTATUS_MACHLEN;
        }
    }

    *data++ = len;
    memcpy(data, buf, len);
    data += len;
    status = htons(data - start);
    memcpy(start + AFPSTATUS_VERSOFF, &status, sizeof(status));
}

/* server signature is a 16-byte quantity */
static uint16_t status_signature(char *data, int *servoffset,
                                 const struct afp_options *options)
{
    char                 *status;
    uint16_t            offset, sigoff;
    status = data;
    /* get server signature offset */
    memcpy(&offset, data + *servoffset, sizeof(offset));
    sigoff = offset = ntohs(offset);
    /* jump to server signature offset */
    data += offset;
    memset(data, 0, 16);
    memcpy(data, options->signature, 16);
    data += 16;
    /* calculate net address offset */
    *servoffset += sizeof(offset);
    offset = htons(data - status);
    memcpy(status + *servoffset, &offset, sizeof(offset));
    return sigoff;
}

static size_t status_netaddress(char *data, int *servoffset,
#ifndef NO_DDP
                                const ASP asp,
#endif
                                const DSI *dsi,
                                const struct afp_options *options)
{
    char               *begin;
    uint16_t          offset;
    size_t             addresses_len = 0;
    begin = data;
    /* get net address offset */
    memcpy(&offset, data + *servoffset, sizeof(offset));
    data += ntohs(offset);
    /* format:
       Address count (byte)
       len (byte = sizeof(length + address type + address)
       address type (byte, ip address = 0x01, ip + port = 0x02,
                           ddp address = 0x03, fqdn = 0x04)
       address (up to 254 bytes, ip = 4, ip + port = 6, ddp = 4)
       */
    /* number of addresses. this currently screws up if we have a dsi
       connection, but we don't have the ip address. to get around this,
       we turn off the status flag for tcp/ip. */
    *data++ = ((options->fqdn && dsi) ? 1 : 0) + (dsi ? 1 : 0) +
#ifndef NO_DDP
              (asp ? 1 : 0) +
#endif
              (((options->flags & OPTION_ANNOUNCESSH) && options->fqdn && dsi) ? 1 : 0);

    /* ip address */
    if (dsi) {
        if (dsi->server.ss_family == AF_INET) { /* IPv4 */
            const struct sockaddr_in *inaddr = (struct sockaddr_in *)&dsi->server;

            if (inaddr->sin_port == htons(DSI_AFPOVERTCP_PORT)) {
                *data++ = 6; /* length */
                *data++ = 0x01; /* basic ip address */
                memcpy(data, &inaddr->sin_addr.s_addr,
                       sizeof(inaddr->sin_addr.s_addr));
                data += sizeof(inaddr->sin_addr.s_addr);
                addresses_len += 7;
            } else {
                /* ip address + port */
                *data++ = 8;
                *data++ = 0x02; /* ip address with port */
                memcpy(data, &inaddr->sin_addr.s_addr,
                       sizeof(inaddr->sin_addr.s_addr));
                data += sizeof(inaddr->sin_addr.s_addr);
                memcpy(data, &inaddr->sin_port, sizeof(inaddr->sin_port));
                data += sizeof(inaddr->sin_port);
                addresses_len += 9;
            }
        } else { /* IPv6 */
            const struct sockaddr_in6 *sa6 = (struct sockaddr_in6 *)&dsi->server;

            if (sa6->sin6_port == htons(DSI_AFPOVERTCP_PORT)) {
                *data++ = 18; /* length */
                *data++ = 6; /* type */
                memcpy(data, &sa6->sin6_addr.s6_addr, sizeof(sa6->sin6_addr.s6_addr));
                data += sizeof(sa6->sin6_addr.s6_addr);
                addresses_len += 19;
            } else {
                /* ip address + port */
                *data++ = 20; /* length */
                *data++ = 7; /* type*/
                memcpy(data, &sa6->sin6_addr.s6_addr, sizeof(sa6->sin6_addr.s6_addr));
                data += sizeof(sa6->sin6_addr.s6_addr);
                memcpy(data, &sa6->sin6_port, sizeof(sa6->sin6_port));
                data += sizeof(sa6->sin6_port);
                addresses_len += 21;
            }
        }
    }

    /* handle DNS names */
    if (options->fqdn && dsi) {
        size_t len = strlen(options->fqdn);

        if (len + 2 + addresses_len < maxstatuslen - offset) {
            *data++ = len + 2;
            *data++ = 0x04;
            memcpy(data, options->fqdn, len);
            data += len;
            addresses_len += len + 2;
        }

        /* Annouce support for SSH tunneled AFP session,
         * this feature is available since 10.3.2.
         * According to the specs (AFP 3.1 p.225) this should
         * be an IP+Port style value, but it only works with
         * a FQDN. OSX Server uses FQDN as well.
         */
        if (len + 2 + addresses_len < maxstatuslen - offset) {
            if (options->flags & OPTION_ANNOUNCESSH) {
                *data++ = len + 2;
                *data++ = 0x05;
                memcpy(data, options->fqdn, len);
                data += len;
            }
        }
    }

#ifndef NO_DDP

    if (asp) {
        const struct sockaddr_at *ddpaddr = atp_sockaddr(asp->asp_atp);
        /* ddp address */
        *data++ = 6;
        *data++ = 0x03; /* ddp address */
        memcpy(data, &ddpaddr->sat_addr.s_net, sizeof(ddpaddr->sat_addr.s_net));
        data += sizeof(ddpaddr->sat_addr.s_net);
        memcpy(data, &ddpaddr->sat_addr.s_node,
               sizeof(ddpaddr->sat_addr.s_node));
        data += sizeof(ddpaddr->sat_addr.s_node);
        memcpy(data, &ddpaddr->sat_port, sizeof(ddpaddr->sat_port));
        data += sizeof(ddpaddr->sat_port);
    }

#endif /* ! NO_DDP */
    /* calculate/store Directory Services Names offset */
    offset = htons(data - begin);
    *servoffset += sizeof(offset);
    memcpy(begin + *servoffset, &offset, sizeof(offset));
    /* return length of buffer */
    return data - begin;
}


/**
 * DirectoryNamesCount offset: uint16_t
 * ...
 * DirectoryNamesCount: uint8_t
 * DirectoryNames: list of UTF-8 Pascal strings (uint8_t + char[1,255])
 */
static size_t status_directorynames(char *data,
                                    int *diroffset,
                                    const DSI *dsi _U_,
                                    const struct afp_options *options)
{
    char *begin = data;
    uint16_t offset;
    memcpy(&offset, begin + *diroffset, sizeof(offset));
    offset = ntohs(offset);
    data += offset;

    if (!uam_gss_enabled() || !options->k5principal) {
        *data = 0;
        data++;
    } else {
        memcpy(data, options->k5principal, options->k5principal_buflen);
        data += options->k5principal_buflen;
    }

    /* Calculate and store offset for UTF8ServerName */
    *diroffset += sizeof(uint16_t);
    offset = htons(data - begin);
    memcpy(begin + *diroffset, &offset, sizeof(uint16_t));
    /* return length of buffer */
    return data - begin;
}

static size_t status_utf8servername(char *data, int *nameoffset,
                                    const DSI *dsi _U_,
                                    const struct afp_options *options)
{
    uint16_t namelen;
    size_t len;
    char *begin = data;
    uint16_t offset;
    const char *server_name;
    memcpy(&offset, data + *nameoffset, sizeof(offset));
    offset = ntohs(offset);
    data += offset;
    server_name = options->servername ? options->servername : options->hostname;
    LOG(log_info, logtype_afpd, "servername: %s", server_name);

    if (dsi) {
        if ((len = convert_string(options->unixcharset,
                                  CH_UTF8_MAC,
                                  server_name,
                                  -1,
                                  data + sizeof(namelen),
                                  maxstatuslen - offset)) == (size_t) - 1) {
            LOG(log_error, logtype_afpd, "Could not set utf8 servername");
            /* set offset to 0 */
            memset(begin + *nameoffset, 0, sizeof(offset));
            data = begin + offset;
        } else {
            namelen = htons(len);
            memcpy(data, &namelen, sizeof(namelen));
            data += sizeof(namelen);
            data += len;
            offset = htons(offset);
            memcpy(begin + *nameoffset, &offset, sizeof(uint16_t));
        }
    } else {
        /* asp connection: set offset to 0 */
        memset(begin + *nameoffset, 0, sizeof(offset));
        data = begin + offset;
    }

    /* return length of buffer */
    return data - begin;
}

/* returns actual offset to signature */
static void status_icon(char *data, const unsigned char *icondata,
                        const size_t iconlen, const int sigoffset)
{
    char                *start = data;
    char                *sigdata = data + sigoffset;
    uint16_t		ret, status;
    memcpy(&status, start + AFPSTATUS_ICONOFF, sizeof(status));

    if (icondata == NULL) {
        ret = status;
        memset(start + AFPSTATUS_ICONOFF, 0, sizeof(status));
    } else {
        data += ntohs(status);
        memcpy(data, icondata, iconlen);
        data += iconlen;
        ret = htons(data - start);
    }

    /* put in signature offset */
    if (sigoffset) {
        memcpy(sigdata, &ret, sizeof(ret));
    }
}

/* ---------------------
 */
void status_init(AFPObj *dsi_obj, AFPObj *asp_obj, DSI *dsi)
{
#ifndef NO_DDP
    ASP asp;
#endif
    char *status = dsi->status;
    size_t statuslen;
    int c, sigoff, ipok = 0;
    const struct afp_options *options = &dsi_obj->options;
    const unsigned char *icon;
    size_t iconlen;
    maxstatuslen = sizeof(dsi->status);
#ifndef NO_DDP

    if (asp_obj->handle) {
        asp = asp_obj->handle;
    } else {
        asp = NULL;
    }

#endif

    if (dsi->server.ss_family == AF_INET) { /* IPv4 */
        const struct sockaddr_in *sa4 = (struct sockaddr_in *)&dsi->server;
        ipok = sa4->sin_addr.s_addr ? 1 : 0;
    } else { /* IPv6 */
        const struct sockaddr_in6 *sa6 = (struct sockaddr_in6 *)&dsi->server;

        for (int i = 0; i < 16; i++) {
            if (sa6->sin6_addr.s6_addr[i]) {
                ipok = 1;
                break;
            }
        }
    }

    /*
     * These routines must be called in order -- earlier calls
     * set the offsets for later calls.
     *
     * using structs is a bad idea, but that's what the original code
     * does. solaris, in fact, will segfault with them. so, now
     * we just use the powers of #defines and memcpy.
     *
     * reply block layout (offsets are 16-bit quantities):
     * machine type offset -> AFP version count offset ->
     * UAM count offset -> vol icon/mask offset -> flags ->
     *
     * server name [padded to even boundary] -> signature offset ->
     * network address offset ->
     *
     * at the appropriate offsets:
     * machine type, afp versions, uams, server signature
     * (16-bytes), network addresses, volume icon/mask
     */
    status_flags(status,
                 options->flags & OPTION_SERVERNOTIF,
                 (options->fqdn || ipok),
                 options->passwdbits,
                 1,
                 options->flags);
    /* returns offset to signature offset */
    c = status_server(status,
                      options->servername ? options->servername : options->hostname, options);
    status_machine(status);
    status_versions(status,
#ifndef NO_DDP
                    NULL,
#endif
                    dsi);
    status_uams(status, options->uamlist);

    if (strcmp(options->legacyicon, "daemon") == 0) {
        icon = daemon_icon;
        iconlen = sizeof(daemon_icon);
    } else if (strcmp(options->legacyicon, "declogo") == 0) {
        icon = declogo_icon;
        iconlen = sizeof(declogo_icon);
    } else if (strcmp(options->legacyicon, "globe") == 0) {
        icon = globe_icon;
        iconlen = sizeof(globe_icon);
    } else if (strcmp(options->legacyicon, "hagar") == 0) {
        icon = hagar_icon;
        iconlen = sizeof(hagar_icon);
    } else if (strcmp(options->legacyicon, "sdcard") == 0) {
        icon = sdcard_icon;
        iconlen = sizeof(sdcard_icon);
    } else if (strcmp(options->legacyicon, "sunlogo") == 0) {
        icon = sunlogo_icon;
        iconlen = sizeof(sunlogo_icon);
    } else {
        icon = tcp_icon;
        iconlen = sizeof(tcp_icon);
    }

    status_icon(status, icon, iconlen, c);
    sigoff = status_signature(status, &c, options);
    /* c now contains the offset where the netaddress offset lives */
    status_netaddress(status, &c,
#ifndef NO_DDP
                      asp,
#endif
                      dsi, options);
    /* c now contains the offset where the Directory Names Count offset lives */
    statuslen = status_directorynames(status, &c, dsi, options);
    /* c now contains the offset where the UTF-8 ServerName offset lives */

    if (statuslen < maxstatuslen) {
        statuslen = status_utf8servername(status, &c, dsi, options);
    }

    /* set dsi status response */
    dsi->signature = status + sigoff;
    dsi->statuslen = statuslen;
    /* end dsi status response */
#ifndef NO_DDP

    /* begin asp status response */
    if (asp_obj->handle) {
        char *aspstatus = asp_obj->aspstatus;
        c = 0;
        statuslen = 0;
        status_flags(aspstatus,
                     options->flags & OPTION_SERVERNOTIF,
                     (options->fqdn || ipok),
                     options->passwdbits,
                     0,
                     options->flags);
        /* returns offset to signature offset */
        c = status_server(aspstatus,
                          options->servername ? options->servername : options->hostname, options);
        status_machine(aspstatus);
        status_versions(aspstatus,
                        asp,
                        NULL);
        status_uams(aspstatus, options->uamlist);

        if (options->legacyicon[0] == '\0') {
            /* if no custom icon set, don't send default icon for asp connections to conserve space if needed */
            icon = NULL;
            iconlen = 0;
        }

        status_icon(aspstatus, icon, iconlen, c);
        sigoff = status_signature(aspstatus, &c, options);
        /* c now contains the offset where the netaddress offset lives */
        status_netaddress(aspstatus, &c,
                          asp,
                          dsi, options);
        /* c now contains the offset where the UTF-8 ServerName offset lives */

        if (statuslen < maxstatuslen) {
            statuslen = status_utf8servername(aspstatus, &c, NULL, options);
        }

        /* set asp status response */
        asp_setstatus(asp, aspstatus, statuslen);
        asp_obj->signature = aspstatus + sigoff;
        asp_obj->statuslen = statuslen;
    }

#endif /* ! NO_DDP */
}

/* set_signature()                                                    */
/*                                                                    */
/* If found in conf file, use it.                                     */
/* If not found in conf file, genarate and append in conf file.       */
/* If conf file don't exist, create and genarate.                     */
/* If cannot open conf file, use one-time signature.                  */
/* If signature = xxxxx, use it.                                      */

void set_signature(struct afp_options *options)
{
    int fd, i;
    struct stat tmpstat;
    char *servername_conf;
    int header = 0;
    char buf[1024], *p;
    FILE *fp = NULL;
    size_t len;
    char *server_tmp;
    server_tmp = options->hostname;
    len = strlen(options->signatureopt);

    if (len == 0) {
        goto server_signature_auto;   /* default */
    } else if (len < 3) {
        LOG(log_warning, logtype_afpd, "WARNING: signature string %s is very short !",
            options->signatureopt);
        goto server_signature_user;
    } else if (len > 16) {
        LOG(log_warning, logtype_afpd, "WARNING: signature string %s is very long !",
            options->signatureopt);
        len = 16;
        goto server_signature_user;
    } else {
        LOG(log_info, logtype_afpd, "signature string is %s.", options->signatureopt);
        goto server_signature_user;
    }

server_signature_user:
    /* Signature is defined in afp.conf */
    memset(options->signature, 0, 16);
    memcpy(options->signature, options->signatureopt, len);
    goto server_signature_done;
server_signature_auto:

    /* Signature type is auto, using afp_signature.conf */
    /* conf file exists? */
    if (!stat(options->sigconffile, &tmpstat)) {
        /* read open? */
        if ((fp = fopen(options->sigconffile, "r")) != NULL) {
            /* scan in the conf file */
            while (fgets(buf, sizeof(buf), fp) != NULL) {
                p = buf;

                while (p && isblank(*p)) {
                    p++;
                }

                if (!p || (*p == '#') || (*p == '\n')) {
                    /* invalid line */
                    continue;
                }

                if (*p == '"') {
                    p++;

                    if ((servername_conf = strtok(p, "\"")) == NULL) {
                        /* syntax error: invalid quoted servername */
                        continue;
                    }
                } else {
                    if ((servername_conf = strtok(p, " \t")) == NULL) {
                        /* syntax error: invalid servername */
                        continue;
                    }
                }

                p = strchr(p, '\0');
                p++;

                if (*p == '\0') {
                    /* syntax error: missing signature */
                    continue;
                }

                if (strcmp(server_tmp, servername_conf)) {
                    /* another servername */
                    continue;
                }

                while (p && isblank(*p)) {
                    p++;
                }

                if (16 == sscanf(p,
                                 "%2hhX%2hhX%2hhX%2hhX%2hhX%2hhX%2hhX%2hhX%2hhX%2hhX%2hhX%2hhX%2hhX%2hhX%2hhX%2hhX",
                                 &options->signature[0], &options->signature[1],
                                 &options->signature[2], &options->signature[3],
                                 &options->signature[4], &options->signature[5],
                                 &options->signature[6], &options->signature[7],
                                 &options->signature[8], &options->signature[9],
                                 &options->signature[10], &options->signature[11],
                                 &options->signature[12], &options->signature[13],
                                 &options->signature[14], &options->signature[15]
                                )) {
                    fclose(fp);
                    /* found in conf file */
                    goto server_signature_done;
                }
            }

            /* append because not found */
            if ((fp = freopen(options->sigconffile, "a+", fp)) != NULL) {
                fseek(fp, 0L, SEEK_END);

                /* size = 0 */
                if (ftell(fp) == 0) {
                    header = 1;
                    goto server_signature_random;
                } else {
                    fseek(fp, -1L, SEEK_END);

                    if (fgetc(fp) != '\n') {
                        /* last char is \n? */
                        fputc('\n', fp);
                    }

                    goto server_signature_random;
                }
            } else {
                LOG(log_error, logtype_afpd,
                    "ERROR: Cannot write in %s (%s). Using one-time signature.",
                    options->sigconffile, strerror(errno));
                goto server_signature_random;
            }
        } else {
            LOG(log_error, logtype_afpd,
                "ERROR: Cannot read %s (%s). Using one-time signature.",
                options->sigconffile, strerror(errno));
            goto server_signature_random;
        }
    } else {
        /* conf file don't exist */
        if ((fd = creat(options->sigconffile, 0644)) < 0) {
            LOG(log_error, logtype_afpd,
                "ERROR: Cannot create %s (%s). Using one-time signature.",
                options->sigconffile, strerror(errno));
            goto server_signature_random;
        }

        if ((fp = fdopen(fd, "w")) == NULL) {
            LOG(log_error, logtype_afpd,
                "ERROR: Cannot fdopen %s (%s). Using one-time signature.",
                options->sigconffile, strerror(errno));
            close(fd);
            goto server_signature_random;
        }

        header = 1;
        goto server_signature_random;
    }

server_signature_random:
    /* generate signature from random number */
    randombytes(options->signature, 16);

    if (fp && header) {
        /* conf file is created or size=0 */
        fprintf(fp, "# DON'T TOUCH NOR COPY THOUGHTLESSLY!\n");
        fprintf(fp, "# This file is auto-generated by afpd.\n");
        fprintf(fp, "# \n");
        fprintf(fp,
                "# ServerSignature is unique identifier used to prevent logging on to\n");
        fprintf(fp, "# the same server twice.\n");
        fprintf(fp, "# \n");
        fprintf(fp,
                "# If setting \"signature = xxxxx\" in afp.conf, this file is not used.\n\n");
    }

    if (fp) {
        fprintf(fp, "\"%s\"\t", server_tmp);

        for (i = 0 ; i < 16 ; i++) {
            fprintf(fp, "%02X", (options->signature)[i]);
        }

        fprintf(fp, "%s", "\n");
        fclose(fp);
    }

server_signature_done:
    /* retrun */
    LOG(log_info, logtype_afpd,
        "signature is %02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X",
        (options->signature)[0], (options->signature)[1],
        (options->signature)[2], (options->signature)[3],
        (options->signature)[4], (options->signature)[5],
        (options->signature)[6], (options->signature)[7],
        (options->signature)[8], (options->signature)[9],
        (options->signature)[10], (options->signature)[11],
        (options->signature)[12], (options->signature)[13],
        (options->signature)[14], (options->signature)[15]);
    return;
}

/* this is the same as asp/dsi_getstatus */
int afp_getsrvrinfo(AFPObj *obj, char *ibuf _U_, size_t ibuflen _U_, char *rbuf,
                    size_t *rbuflen)
{
#ifndef NO_DDP

    if (obj->proto == AFPPROTO_DSI) {
#endif
        memcpy(rbuf, obj->dsi->status, obj->dsi->statuslen);
        *rbuflen = obj->dsi->statuslen;
#ifndef NO_DDP
    } else {
        memcpy(rbuf, obj->aspstatus, obj->statuslen);
        *rbuflen = obj->statuslen;
    }

#endif
    return AFP_OK;
}
