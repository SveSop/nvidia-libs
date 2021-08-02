nvencodeapi_src = [
  'nvencodeapi.c',
]

arch_dir_prefix = target_machine.cpu_family() == 'x86_64' ? 'x86_64-' : 'i386-'

install_dir_unix    = install_dir / arch_dir_prefix + 'unix'
install_dir_windows = install_dir / arch_dir_prefix + 'windows'


nvencodeapi_res_target = custom_target('nvencodeapi.res',
  output  : 'nvencodeapi.res',
  input   : 'nvencodeapi.rc',
  command : [wrc, target_arch, '-I.', '-I'+meson.source_root()+'/include', '-D__WINESRC__', '-o', '@OUTPUT@', '@INPUT@'],
  install : false)


nvencodeapi_dll = shared_library('nvencodeapi.dll', nvencodeapi_src,
  name_prefix         : '',
  include_directories : include_path,
  dependencies        : [ lib_dl ],
  objects             : 'nvencodeapi.spec',
  install             : true,
  install_dir         : install_dir_unix)


nvencodeapi_dll_target = custom_target('nvencodeapi.dll',
  output  : 'nvencodeapi.dll',
  input   : [ 'nvencodeapi.spec', nvencodeapi_res_target ],
  command : [ winebuild, target_arch, '--dll', '--fake-module', '-E', '@INPUT@', '-o', '@OUTPUT@', '-F', 'nvencodeapi.dll' ],
  install : true,
  install_dir : install_dir_windows)


nvencodeapi_def_target = custom_target('nvencodeapi.def',
  output  : 'nvencodeapi.def',
  input   : 'nvencodeapi.spec',
  command : [ winebuild, target_arch, '-w', '--def', '--export', '@INPUT@', '-o', '@OUTPUT@' ],
  install : false)
