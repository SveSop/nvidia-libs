nvencodeapi64_src = [
  '../nvencodeapi/nvencodeapi.c',
]

arch_dir_prefix = target_machine.cpu_family() == 'x86_64' ? 'x86_64-' : 'i386-'

install_dir_unix    = install_dir / arch_dir_prefix + 'unix'
install_dir_windows = install_dir / arch_dir_prefix + 'windows'

thread_dep = dependency('threads')

nvencodeapi64_res_target = custom_target('nvencodeapi64.res',
  output  : 'nvencodeapi64.res',
  input   : 'nvencodeapi64.rc',
  command : [ wrc, target_arch, '--nostdinc', '-I.', '-I'+meson.source_root()+'/include', '-D__WINESRC__', '-o', '@OUTPUT@', '@INPUT@' ],
  install : false)


nvencodeapi64_dll = shared_library('nvencodeapi64.dll', nvencodeapi64_src,
  name_prefix         : '',
  dependencies        : [ thread_dep, lib_dl ],
  include_directories : include_path,
  objects             : '../nvencodeapi/nvencodeapi.spec',
  install             : true,
  install_dir         : install_dir_unix)


nvencodeapi64_def_target = custom_target('nvencodeapi64.def',
  output  : 'nvencodeapi64.def',
  input   : '../nvencodeapi/nvencodeapi.spec',
  command : [ winebuild, target_arch, '-w', '--def', '-o', '@OUTPUT@', '-E', '@INPUT@' ],
  install : false)


nvencodeapi64_dll_target = custom_target('nvencodeapi64.dll',
  output  : 'nvencodeapi64.dll',
  input   : [ nvencodeapi64_def_target, nvencodeapi64_res_target ],
  command : [ winebuild, target_arch, '--dll', '--fake-module', '-o', '@OUTPUT@', '-E', '@INPUT@' ],
  install : true,
  install_dir : install_dir_windows)
