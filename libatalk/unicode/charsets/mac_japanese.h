/*
 * MacJapanese
 * Copyright (C) TSUBAKIMOTO Hiroya <zorac@4000do.co.jp> 2004
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Reference
 * http://www.unicode.org/Public/MAPPINGS/VENDORS/APPLE/
 */

static const uint16_t mac_japanese_uni2_page00[][2] = {
    /* 0x00a */ { 0x0201,    1 },
};

static const uint16_t mac_japanese_uni2_page20[][2] = {
    /* 0x201 */ { 0x0030,    3 }, { 0x0000,    0 }, { 0x4000,    5 },
    /* 0x204 */ { 0x0000,    0 }, { 0x0000,    0 }, { 0x0000,    0 }, { 0x0000,    0 },
    /* 0x208 */ { 0x0000,    0 }, { 0x0000,    0 }, { 0x0000,    0 }, { 0x0000,    0 },
    /* 0x20c */ { 0x0000,    0 }, { 0x0000,    0 }, { 0x0000,    0 }, { 0x0000,    0 },
    /* 0x210 */ { 0x0200,    6 }, { 0x0048,    7 }, { 0x0006,    9 }, { 0x0000,    0 },
    /* 0x214 */ { 0x0000,    0 }, { 0x0000,    0 }, { 0x0fff,   11 }, { 0x0fff,   23 },
    /* 0x218 */ { 0x0000,    0 }, { 0x0000,    0 }, { 0x0000,    0 }, { 0x0000,    0 },
    /* 0x21c */ { 0x0070,   35 }, { 0x0000,    0 }, { 0x03c0,   38 }, { 0x0000,    0 },
    /* 0x220 */ { 0x0000,    0 }, { 0x8000,   42 }, { 0x4000,   43 }, { 0x0000,    0 },
    /* 0x224 */ { 0x0000,    0 }, { 0x0000,    0 }, { 0x0000,    0 }, { 0x0000,    0 },
    /* 0x228 */ { 0x0000,    0 }, { 0x0000,    0 }, { 0x0000,    0 }, { 0x8000,   44 },
};

static const uint16_t mac_japanese_uni2_page24[][2] = {
    /* 0x246 */ { 0xffff,   45 }, { 0xffff,   61 },
    /* 0x248 */ { 0xffff,   77 }, { 0xf001,   93 }, { 0xffff,   98 }, { 0x003f,  114 },
};

static const uint16_t mac_japanese_uni2_page26[][2] = {
    /* 0x260 */ { 0x4000,  120 }, { 0xf000,  121 }, { 0x0000,    0 }, { 0x0000,    0 },
    /* 0x264 */ { 0x0000,    0 }, { 0x0000,    0 }, { 0x00ff,  125 }, { 0x0000,    0 },
    /* 0x268 */ { 0x0000,    0 }, { 0x0000,    0 }, { 0x0000,    0 }, { 0x0000,    0 },
    /* 0x26c */ { 0x0000,    0 }, { 0x0000,    0 }, { 0x0000,    0 }, { 0x0000,    0 },
    /* 0x270 */ { 0x0000,    0 }, { 0x0000,    0 }, { 0x0000,    0 }, { 0x0000,    0 },
    /* 0x274 */ { 0x0000,    0 }, { 0x0000,    0 }, { 0x0000,    0 }, { 0x7fc0,  133 },
};

static const uint16_t mac_japanese_uni2_page30[][2] = {
    /* 0x300 */ { 0x0010,  142 }, { 0xa000,  143 }, { 0x0001,  145 }, { 0x0000,    0 },
    /* 0x304 */ { 0x0000,    0 }, { 0x0000,    0 }, { 0x0000,    0 }, { 0x0000,    0 },
    /* 0x308 */ { 0x0000,    0 }, { 0x0010,  146 }, { 0x0000,    0 }, { 0x0000,    0 },
    /* 0x30c */ { 0x0000,    0 }, { 0x0000,    0 }, { 0x0000,    0 }, { 0x0780,  147 },
};

static const uint16_t mac_japanese_uni2_page32[][2] = {
    /* 0x322 */ { 0xfc00,  151 }, { 0xffff,  157 },
    /* 0x324 */ { 0x000d,  173 }, { 0x0000,    0 }, { 0x0000,    0 }, { 0x0000,    0 },
    /* 0x328 */ { 0x0000,    0 }, { 0x6340,  176 }, { 0x03f0,  181 }, { 0x0000,    0 },
    /* 0x32c */ { 0x0000,    0 }, { 0x0000,    0 }, { 0x0000,    0 }, { 0x0000,    0 },
    /* 0x330 */ { 0x2029,  187 }, { 0x4170,  191 }, { 0x0ccc,  196 }, { 0x0a4a,  202 },
    /* 0x334 */ { 0x6684,  207 }, { 0x0082,  213 }, { 0x0000,    0 }, { 0xf800,  215 },
    /* 0x338 */ { 0xc0e0,  220 }, { 0xf1c1,  225 }, { 0x0037,  233 }, { 0x000f,  238 },
    /* 0x33c */ { 0x2810,  242 }, { 0x0010,  245 },
};

static const uint16_t mac_japanese_uni2_pagee0[][2] = {
    /* 0xe00 */ { 0xffff,  246 }, { 0xffff,  262 }, { 0x0fff,  278 }, { 0x001f,  290 },
    /* 0xe04 */ { 0x7f00,  295 },
};

static const uint16_t mac_japanese_uni2_pagefe[][2] = {
    /* 0xfe3 */ { 0xffeb,  302 },
    /* 0xfe4 */ { 0x001f,  316 }, { 0x0000,    0 }, { 0x0000,    0 }, { 0x0000,    0 },
    /* 0xfe8 */ { 0x0000,    0 }, { 0x0000,    0 }, { 0x0000,    0 }, { 0x0000,    0 },
    /* 0xfec */ { 0x0000,    0 }, { 0x0000,    0 }, { 0x0000,    0 }, { 0x0000,    0 },
    /* 0xff0 */ { 0x0000,    0 }, { 0x0000,    0 }, { 0x0000,    0 }, { 0x1000,  321 },
};

static const cjk_index_t mac_japanese_uni2_index[] = {
    { { 0x00a0, 0x00af }, mac_japanese_uni2_page00 },
    { { 0x2010, 0x22bf }, mac_japanese_uni2_page20 },
    { { 0x2460, 0x24bf }, mac_japanese_uni2_page24 },
    { { 0x2600, 0x277f }, mac_japanese_uni2_page26 },
    { { 0x3000, 0x30ff }, mac_japanese_uni2_page30 },
    { { 0x3220, 0x33df }, mac_japanese_uni2_page32 },
    { { 0xe000, 0xe04f }, mac_japanese_uni2_pagee0 },
    { { 0xfe30, 0xff3f }, mac_japanese_uni2_pagefe },
    { { 0, 0 }, NULL }
};

static const uint16_t mac_japanese_uni2_charset[] = {
    0x0080, 0x00a0, 0x00fd, 0x815c, 0xffff, 0xffff, 0x8656, 0x8650,
    0x869b, 0x869d, 0x00fe, 0x859f, 0x85a0, 0x85a1, 0x85a2, 0x85a3,
    0x85a4, 0x85a5, 0x85a6, 0x85a7, 0x85a8, 0x85a9, 0x85aa, 0x85b3,
    0x85b4, 0x85b5, 0x85b6, 0x85b7, 0x85b8, 0x85b9, 0x85ba, 0x85bb,
    0x85bc, 0x85bd, 0x85be, 0x86cc, 0x86cd, 0x86cb, 0x86d0, 0x86d1,
    0x86cf, 0x86d2, 0x8841, 0x8840, 0x8842, 0x8540, 0x8541, 0x8542,
    0x8543, 0x8544, 0x8545, 0x8546, 0x8547, 0x8548, 0x8549, 0x854a,
    0x854b, 0x854c, 0x854d, 0x854e, 0x854f, 0x8550, 0x8551, 0x8552,
    0x8553, 0x855e, 0x855f, 0x8560, 0x8561, 0x8562, 0x8563, 0x8564,
    0x8565, 0x8566, 0x8567, 0x8568, 0x8569, 0x856a, 0x856b, 0x856c,
    0x856d, 0x856e, 0x856f, 0x8570, 0x8571, 0x8592, 0x8593, 0x8594,
    0x8595, 0x8596, 0x8597, 0x8598, 0x8599, 0x859a, 0x85db, 0x85dc,
    0x85dd, 0x85de, 0x85df, 0x85e0, 0x85e1, 0x85e2, 0x85e3, 0x85e4,
    0x85e5, 0x85e6, 0x85e7, 0x85e8, 0x85e9, 0x85ea, 0x85eb, 0x85ec,
    0x85ed, 0x85ee, 0x85ef, 0x85f0, 0x85f1, 0x85f2, 0x85f3, 0x85f4,
    0x86b4, 0x86c8, 0x86c9, 0x86c7, 0x86ca, 0x86a3, 0x86a1, 0x86a2,
    0x86a4, 0x869f, 0x86a5, 0x86a6, 0x86a0, 0x857c, 0x857d, 0x857e,
    0x8580, 0x8581, 0x8582, 0x8583, 0x8584, 0x8585, 0x86b5, 0x8854,
    0x8855, 0x86b3, 0x8868, 0x886a, 0x886b, 0x886c, 0x886d, 0x8741,
    0x8742, 0x8743, 0x8744, 0x8745, 0x8746, 0x8740, 0x874d, 0x8750,
    0x8753, 0x874f, 0x8754, 0x8752, 0x8748, 0x8758, 0x874b, 0x874c,
    0x8751, 0x8755, 0x8756, 0x874e, 0x8757, 0x8747, 0x8749, 0x874a,
    0x8799, 0x879b, 0x879e, 0x879a, 0x879c, 0x8793, 0x8794, 0x8795,
    0x8796, 0x8797, 0x8798, 0x87bd, 0x87a7, 0x87a4, 0x87b0, 0x87a2,
    0x87aa, 0x87a3, 0x87a9, 0x87be, 0x87a0, 0x87b2, 0x87b3, 0x87ab,
    0x87bf, 0x87b5, 0x87c0, 0x87a5, 0x87a8, 0x87ae, 0x87b4, 0x87b1,
    0x87c1, 0x879f, 0x87ad, 0x87a1, 0x87a6, 0x87ac, 0x87af, 0x87e8,
    0x87e7, 0x87e6, 0x87e5, 0x87fa, 0x865a, 0x865b, 0x865c, 0x864a,
    0x864c, 0x8659, 0x864e, 0x864f, 0x8651, 0x8640, 0x8642, 0x8648,
    0x8641, 0x8643, 0x8646, 0x8649, 0x8644, 0x8647, 0x8655, 0x8654,
    0x8653, 0x8652, 0x864d, 0x8658, 0x869c, 0x8657, 0xeb5d, 0xeb61,
    0xeb63, 0x00ff, 0x86d4, 0x86d5, 0x86d3, 0x86d6, 0xeb41, 0xeb42,
    0xeb60, 0xec9f, 0xeca1, 0xeca3, 0xeca5, 0xeca7, 0xecc1, 0xece1,
    0xece3, 0xece5, 0xecec, 0xed40, 0xed42, 0xed44, 0xed46, 0xed48,
    0xed62, 0xed83, 0xed85, 0xed87, 0xed8e, 0xed95, 0xed96, 0xeb5b,
    0x8791, 0x8792, 0x879d, 0x85ab, 0x85bf, 0x87fb, 0x87fc, 0x869e,
    0x85ac, 0x85c0, 0x8591, 0x865d, 0x85ad, 0x85c1, 0x86ce, 0xeb81,
    0xeb6d, 0xeb6e, 0x864b, 0x8645, 0xeb62, 0xeb50, 0xeb64, 0xeb5c,
    0xeb51, 0xeb69, 0xeb6a, 0xeb6f, 0xeb70, 0xeb6b, 0xeb6c, 0xeb79,
    0xeb7a, 0xeb73, 0xeb74, 0xeb71, 0xeb72, 0xeb75, 0xeb76, 0xeb77,
    0xeb78, 0x815f,
};

static const uint16_t mac_japanese_2uni_page00[][2] = {
    /* 0x008 */ { 0x0001,    0 }, { 0x0000,    0 }, { 0x0001,    1 }, { 0x0000,    0 },
    /* 0x00c */ { 0x0000,    0 }, { 0x0000,    0 }, { 0x0000,    0 }, { 0xe000,    2 },
};

static const uint16_t mac_japanese_2uni_page81[][2] = {
    /* 0x815 */ { 0x9000,    5 },
};

static const uint16_t mac_japanese_2uni_page85[][2] = {
    /* 0x854 */ { 0xffff,    7 }, { 0xc00f,   23 }, { 0xffff,   29 }, { 0x7003,   45 },
    /* 0x858 */ { 0x003f,   50 }, { 0x87fe,   56 }, { 0x3fff,   67 }, { 0xfff8,   81 },
    /* 0x85c */ { 0x0003,   94 }, { 0xf800,   96 }, { 0xffff,  101 }, { 0x001f,  117 },
    /* 0x860 */ { 0x0000,    0 }, { 0x0000,    0 }, { 0x0000,    0 }, { 0x0000,    0 },
    /* 0x864 */ { 0xffff,  122 }, { 0x3fff,  138 }, { 0x0000,    0 }, { 0x0000,    0 },
    /* 0x868 */ { 0x0000,    0 }, { 0xf800,  152 }, { 0x007f,  157 }, { 0x0038,  164 },
    /* 0x86c */ { 0xff80,  167 }, { 0x007f,  176 }, { 0x0000,    0 }, { 0x0000,    0 },
    /* 0x870 */ { 0x0000,    0 }, { 0x0000,    0 }, { 0x0000,    0 }, { 0x0000,    0 },
    /* 0x874 */ { 0xffff,  183 }, { 0x01ff,  199 }, { 0x0000,    0 }, { 0x0000,    0 },
    /* 0x878 */ { 0x0000,    0 }, { 0xfffe,  208 }, { 0xffff,  223 }, { 0xe03f,  239 },
    /* 0x87c */ { 0x0003,  248 }, { 0x0000,    0 }, { 0x01e0,  250 }, { 0x1c00,  254 },
    /* 0x880 */ { 0x0000,    0 }, { 0x0000,    0 }, { 0x0000,    0 }, { 0x0000,    0 },
    /* 0x884 */ { 0x0007,  257 }, { 0x0030,  260 }, { 0x3d00,  262 },
};

static const uint16_t mac_japanese_2uni_pageeb[][2] = {
    /* 0xeb4 */ { 0x0006,  267 }, { 0x3803,  269 }, { 0xfe1f,  274 }, { 0x07ff,  286 },
    /* 0xeb8 */ { 0x0002,  297 }, { 0x0000,    0 }, { 0x0000,    0 }, { 0x0000,    0 },
    /* 0xebc */ { 0x0000,    0 }, { 0x0000,    0 }, { 0x0000,    0 }, { 0x0000,    0 },
    /* 0xec0 */ { 0x0000,    0 }, { 0x0000,    0 }, { 0x0000,    0 }, { 0x0000,    0 },
    /* 0xec4 */ { 0x0000,    0 }, { 0x0000,    0 }, { 0x0000,    0 }, { 0x0000,    0 },
    /* 0xec8 */ { 0x0000,    0 }, { 0x8000,  298 }, { 0x00aa,  299 }, { 0x0000,    0 },
    /* 0xecc */ { 0x0002,  303 }, { 0x0000,    0 }, { 0x102a,  304 }, { 0x0000,    0 },
    /* 0xed0 */ { 0x0000,    0 }, { 0x0000,    0 }, { 0x0000,    0 }, { 0x0000,    0 },
    /* 0xed4 */ { 0x0155,  308 }, { 0x0000,    0 }, { 0x0004,  313 }, { 0x0000,    0 },
    /* 0xed8 */ { 0x40a8,  314 }, { 0x0060,  318 },
};

static const cjk_index_t mac_japanese_2uni_index[] = {
    { { 0x0080, 0x00ff }, mac_japanese_2uni_page00 },
    { { 0x8150, 0x815f }, mac_japanese_2uni_page81 },
    { { 0x8540, 0x886f }, mac_japanese_2uni_page85 },
    { { 0xeb40, 0xed9f }, mac_japanese_2uni_pageeb },
    { { 0, 0 }, NULL }
};

static const uint16_t mac_japanese_2uni_charset[] = {
    0x005c, 0x00a0, 0x00a9, 0x2122, 0xe003, 0x2014, 0xff3c, 0x2460,
    0x2461, 0x2462, 0x2463, 0x2464, 0x2465, 0x2466, 0x2467, 0x2468,
    0x2469, 0x246a, 0x246b, 0x246c, 0x246d, 0x246e, 0x246f, 0x2470,
    0x2471, 0x2472, 0x2473, 0x2474, 0x2475, 0x2476, 0x2477, 0x2478,
    0x2479, 0x247a, 0x247b, 0x247c, 0x247d, 0x247e, 0x247f, 0x2480,
    0x2481, 0x2482, 0x2483, 0x2484, 0x2485, 0x2486, 0x2487, 0x2776,
    0x2777, 0x2778, 0x2779, 0x277a, 0x277b, 0x277c, 0x277d, 0x277e,
    0xe030, 0x2488, 0x2489, 0x248a, 0x248b, 0x248c, 0x248d, 0x248e,
    0x248f, 0x2490, 0x2160, 0x2161, 0x2162, 0x2163, 0x2164, 0x2165,
    0x2166, 0x2167, 0x2168, 0x2169, 0x216a, 0x216b, 0xe025, 0xe02a,
    0xe032, 0x2170, 0x2171, 0x2172, 0x2173, 0x2174, 0x2175, 0x2176,
    0x2177, 0x2178, 0x2179, 0x217a, 0x217b, 0xe026, 0xe02b, 0xe033,
    0x249c, 0x249d, 0x249e, 0x249f, 0x24a0, 0x24a1, 0x24a2, 0x24a3,
    0x24a4, 0x24a5, 0x24a6, 0x24a7, 0x24a8, 0x24a9, 0x24aa, 0x24ab,
    0x24ac, 0x24ad, 0x24ae, 0x24af, 0x24b0, 0x24b1, 0x24b2, 0x24b3,
    0x24b4, 0x24b5, 0x339c, 0x339f, 0x339d, 0x33a0, 0x33a4, 0xe04c,
    0x33a1, 0x33a5, 0x339e, 0x33a2, 0x338e, 0xe04b, 0x338f, 0x33c4,
    0x3396, 0x3397, 0x2113, 0x3398, 0x33b3, 0x33b2, 0x33b1, 0x33b0,
    0x2109, 0x33d4, 0x33cb, 0x3390, 0x3385, 0x3386, 0x3387, 0xe031,
    0x2116, 0x33cd, 0x2121, 0xe029, 0x2664, 0x2667, 0x2661, 0x2662,
    0x2660, 0x2663, 0x2665, 0x2666, 0x3020, 0x260e, 0x3004, 0x261e,
    0x261c, 0x261d, 0x261f, 0x21c6, 0x21c4, 0x21c5, 0xe034, 0x21e8,
    0x21e6, 0x21e7, 0x21e9, 0xe006, 0xe004, 0xe005, 0xe007, 0x3230,
    0x322a, 0x322b, 0x322c, 0x322d, 0x322e, 0x322f, 0x3240, 0x3237,
    0x3242, 0x3243, 0x3239, 0x323a, 0x3231, 0x323e, 0x3234, 0x3232,
    0x323b, 0x3236, 0x3233, 0x3235, 0x323c, 0x323d, 0x323f, 0x3238,
    0xe022, 0xe023, 0x32a4, 0x32a5, 0x32a6, 0x32a7, 0x32a8, 0x32a9,
    0x3296, 0x329d, 0x3298, 0x329e, 0xe024, 0x3299, 0x3349, 0x3322,
    0x334d, 0x3314, 0x3316, 0x3305, 0x3333, 0x334e, 0x3303, 0x3336,
    0x3318, 0x3315, 0x3327, 0x3351, 0x334a, 0x3339, 0x3357, 0x330d,
    0x3342, 0x3323, 0x3326, 0x333b, 0x332b, 0x3300, 0x331e, 0x332a,
    0x3331, 0x3347, 0x337e, 0x337d, 0x337c, 0x337b, 0x337f, 0xe027,
    0xe028, 0x222e, 0x221f, 0x22bf, 0x301d, 0x301f, 0x3094, 0x30f7,
    0x30f8, 0x30f9, 0x30fa, 0xe008, 0xe009, 0xe04e, 0xfe33, 0xe021,
    0xfe31, 0xe000, 0xe00a, 0xe001, 0xe04d, 0xe002, 0xfe30, 0xfe35,
    0xfe36, 0xfe39, 0xfe3a, 0xe049, 0xe04a, 0xfe37, 0xfe38, 0xfe3f,
    0xfe40, 0xfe3d, 0xfe3e, 0xfe41, 0xfe42, 0xfe43, 0xfe44, 0xfe3b,
    0xfe3c, 0xe048, 0xe00b, 0xe00c, 0xe00d, 0xe00e, 0xe00f, 0xe010,
    0xe011, 0xe012, 0xe013, 0xe014, 0xe015, 0xe016, 0xe017, 0xe018,
    0xe019, 0xe01a, 0xe01b, 0xe01c, 0xe01d, 0xe01e, 0xe01f, 0xe020,
};

static const uint32_t mac_japanese_compose[] = {
    0x2010f87e, 0x2016f87e, 0x2026f87e, 0x2026f87f,
    0x21e6f87a, 0x21e7f87a, 0x21e8f87a, 0x21e9f87a,
    0x3001f87e, 0x3002f87e, 0x301cf87e, 0x3041f87e,
    0x3043f87e, 0x3045f87e, 0x3047f87e, 0x3049f87e,
    0x3063f87e, 0x3083f87e, 0x3085f87e, 0x3087f87e,
    0x308ef87e, 0x30a1f87e, 0x30a3f87e, 0x30a5f87e,
    0x30a7f87e, 0x30a9f87e, 0x30c3f87e, 0x30e3f87e,
    0x30e5f87e, 0x30e7f87e, 0x30eef87e, 0x30f5f87e,
    0x30f6f87e, 0x30fcf87e, 0x592720dd, 0x5c0f20dd,
    0x63a720dd, 0xe02c0049, 0xe02d0069, 0xe02e793e,
    0xe02f4eba, 0xe0350058, 0xe0360056, 0xe0370076,
    0xe0380049, 0xe0390069, 0xe03a4f1a, 0xe03b6cd5,
    0xe03c002e, 0xe03d0042, 0xe03e0056, 0xe03f0076,
    0xe0402191, 0xe0410041, 0xe0420049, 0xe0430069,
    0xe0440049, 0xe0450069, 0xe0469650, 0xe04756e3,
    0xf8600030, 0xf8600054, 0xf8600058, 0xf8600078,
    0xf8602193, 0xf8610046, 0xf8610058, 0xf8610078,
    0xf8620058, 0xf8620078, 0xf8626709, 0xf8628ca1,
    0xff1df87e, 0xff3bf87e, 0xff3df87e, 0xff47f87f,
    0xff4df87f, 0xff5cf87e, 0xffe3f87e,
};
