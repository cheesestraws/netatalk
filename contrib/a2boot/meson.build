a2boot_deps = []

if have_iconv
    a2boot_deps += iconv
endif

a2boot_c_args = [
    '-D_PATH_A_GS_BLOCKS="' + pkgconfdir + '/a2boot/ProDOS16 Boot Blocks"',
    '-D_PATH_A_2E_BLOCKS="'
    + pkgconfdir
    + '/a2boot/Apple :2f:2fe Boot Blocks"',
    '-D_PATH_P16_IMAGE="' + pkgconfdir + '/a2boot/ProDOS16 Image"',
    dversion,
]

executable(
    'a2boot',
    'a2boot.c',
    include_directories: root_includes,
    link_with: libatalk,
    dependencies: a2boot_deps,
    c_args: a2boot_c_args,
    install: true,
    install_dir: sbindir,
    build_rpath: rpath_libdir,
    install_rpath: rpath_libdir,
)
