nvcuvid_src = [
  'nvcuvid.c',
]

arch_dir_prefix = target_machine.cpu_family() == 'x86_64' ? 'x86_64-' : 'i386-'

install_dir_unix    = install_dir / arch_dir_prefix + 'unix'
install_dir_windows = install_dir / arch_dir_prefix + 'windows'


nvcuvid_res_target = custom_target('nvcuvid.res',
  output  : 'nvcuvid.res',
  input   : 'nvcuvid.rc',
  command : [wrc, target_arch, '-I.', '-I'+meson.source_root()+'/include', '-D__WINESRC__', '-o', '@OUTPUT@', '@INPUT@'],
  install : false)


nvcuvid_dll = shared_library('nvcuvid.dll', nvcuvid_src,
  name_prefix         : '',
  include_directories : include_path,
  dependencies        : [ lib_dl ],
  objects             : 'nvcuvid.spec',
  install             : true,
  install_dir         : install_dir_unix)


nvcuvid_dll_target = custom_target('nvcuvid.dll',
  output  : 'nvcuvid.dll',
  input   : [ 'nvcuvid.spec', nvcuvid_res_target ],
  command : [ winebuild, target_arch, '--dll', '--fake-module', '-E', '@INPUT@', '-o', '@OUTPUT@', '-F', 'nvcuvid.dll' ],
  install : true,
  install_dir : install_dir_windows)


nvcuvid_def_target = custom_target('nvcuvid.def',
  output  : 'nvcuvid.def',
  input   : 'nvcuvid.spec',
  command : [ winebuild, target_arch, '-w', '--def', '--export', '@INPUT@', '-o', '@OUTPUT@' ],
  install : false)
