nvencodeapi64_src = [
  '../nvencodeapi/nvencodeapi.c',
]

arch_dir_prefix = target_machine.cpu_family() == 'x86_64' ? 'x86_64-' : 'i386-'

install_dir_unix    = install_dir / arch_dir_prefix + 'unix'
install_dir_windows = install_dir / arch_dir_prefix + 'windows'


nvencodeapi64_res_target = custom_target('nvencodeapi64.res',
  output  : 'nvencodeapi64.res',
  input   : 'nvencodeapi64.rc',
  command : [wrc, target_arch, '-I.', '-I'+meson.source_root()+'/include', '-D__WINESRC__', '-o', '@OUTPUT@', '@INPUT@'],
  install : false)


nvencodeapi64_dll = shared_library('nvencodeapi64.dll', nvencodeapi64_src,
  name_prefix         : '',
  include_directories : include_path,
  dependencies        : [ lib_dl ],
  objects             : 'nvencodeapi64.spec',
  install             : true,
  install_dir         : install_dir_unix)


nvencodeapi64_dll_target = custom_target('nvencodeapi64.dll',
  output  : 'nvencodeapi64.dll',
  input   : [ 'nvencodeapi64.spec', nvencodeapi64_res_target ],
  command : [ winebuild, target_arch, '--dll', '--fake-module', '-E', '@INPUT@', '-o', '@OUTPUT@', '-F', 'nvencodeapi64.dll' ],
  install : true,
  install_dir : install_dir_windows)


nvencodeapi64_def_target = custom_target('nvencodeapi64.def',
  output  : 'nvencodeapi64.def',
  input   : 'nvencodeapi64.spec',
  command : [ winebuild, target_arch, '-w', '--def', '--export', '@INPUT@', '-o', '@OUTPUT@' ],
  install : false)
