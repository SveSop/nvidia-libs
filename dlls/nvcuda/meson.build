nvcuda_src = [
  'internal.c',
  'nvcuda.c',
  'function_mappings.c',
  'encryption.c',
]

arch_dir_prefix = target_machine.cpu_family() == 'x86_64' ? 'x86_64-' : 'i386-'

install_dir_unix    = install_dir / arch_dir_prefix + 'unix'
install_dir_windows = install_dir / arch_dir_prefix + 'windows'

thread_dep = dependency('threads')

nvcuda_res_target = custom_target('nvcuda.res',
  output  : 'nvcuda.res',
  input   : 'nvcuda.rc',
  command : [ wrc, target_arch, '--nostdinc', '-I.', '-I'+meson.source_root()+'/include', '-D__WINESRC__', '-o', '@OUTPUT@', '@INPUT@' ],
  install : false)


nvcuda_dll = shared_library('nvcuda.dll', nvcuda_src,
  name_prefix         : '',
  dependencies        : [ thread_dep, lib_dl ],
  include_directories : include_path,
  objects             : 'nvcuda.spec',
  install             : true,
  install_dir         : install_dir_unix)


nvcuda_def_target = custom_target('nvcuda.def',
  output  : 'nvcuda.def',
  input   : 'nvcuda.spec',
  command : [ winebuild, target_arch, '-w', '--def', '-o', '@OUTPUT@', '-E', '@INPUT@' ],
  install : false)


nvcuda_dll_target = custom_target('nvcuda.dll',
  output  : 'nvcuda.dll',
  input   : [ nvcuda_def_target, nvcuda_res_target ],
  command : [ winebuild, target_arch, '--dll', '--fake-module', '-o', '@OUTPUT@', '-E', '@INPUT@' ],
  install : true,
  install_dir : install_dir_windows)
