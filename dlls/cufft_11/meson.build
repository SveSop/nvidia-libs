nvcuda_src = [
  'cufft.c',
]

arch_dir_prefix = target_machine.cpu_family() == 'x86_64' ? 'x86_64-' : 'i386-'

install_dir_unix    = install_dir / arch_dir_prefix + 'unix'
install_dir_windows = install_dir / arch_dir_prefix + 'windows'

thread_dep = dependency('threads')

cufft_res_target = custom_target('cufft.res',
  output  : 'cufft.res',
  input   : 'cufft.rc',
  command : [ wrc, target_arch, '--nostdinc', '-I.', '-I'+meson.source_root()+'/include', '-D__WINESRC__', '-o', '@OUTPUT@', '@INPUT@' ],
  install : false)


cufft_dll = shared_library('cufft64_11.dll', nvcuda_src,
  name_prefix         : '',
  dependencies        : [ thread_dep, lib_dl ],
  include_directories : include_path,
  objects             : 'cufft.spec',
  install             : true,
  install_dir         : install_dir_unix)


cufft_def_target = custom_target('cufft.def',
  output  : 'cufft.def',
  input   : 'cufft.spec',
  command : [ winebuild, target_arch, '-w', '--def', '-o', '@OUTPUT@', '-E', '@INPUT@' ],
  install : false)


cufft_dll_target = custom_target('cufft64_11.dll',
  output  : 'cufft64_11.dll',
  input   : [ cufft_def_target, cufft_res_target ],
  command : [ winebuild, target_arch, '--dll', '--fake-module', '-o', '@OUTPUT@', '-E', '@INPUT@' ],
  install : true,
  install_dir : install_dir_windows)
