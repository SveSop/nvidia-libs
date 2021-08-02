nvml_res_target = custom_target('nvml.res',
    output  : 'nvml.res',
    input   : 'nvml.rc',
    command : [wrc, target_arch, '-I.', '-I'+meson.source_root()+'/include', '-D__WINESRC__', '-o', '@OUTPUT@', '@INPUT@'],
    install : false)

arch_dir_prefix = target_machine.cpu_family() == 'x86_64' ? 'x86_64-' : 'i386-'

install_dir_unix    = install_dir / arch_dir_prefix + 'unix'
install_dir_windows = install_dir / arch_dir_prefix + 'windows'


nvml_def_target = custom_target('libnvml.def',
    output      : 'libnvml.def',
    input       : 'nvml.spec',
    command     : [winebuild, target_arch, '--def', '-o', '@OUTPUT@', '-E', '@INPUT@'],
    install : false)


nvml_dll_target = custom_target('nvml.dll',
    output      : 'nvml.dll',
    input       : [nvml_def_target, nvml_res_target],
    command     : [winebuild, target_arch, '--dll', '--fake-module', '-o', '@OUTPUT@', '-E', '@INPUT@'],
    install     : true,
    install_dir : install_dir_windows)


nvml_dll = shared_library('nvml.dll', ['nvml.c'],
    name_prefix  : '',
    include_directories : include_path,
    dependencies : [lib_dl],
    link_depends : [nvml_def_target],
    link_args    : [meson.current_build_dir() / 'libnvml.def'],
    install      : true,
    install_dir  : install_dir_unix)
