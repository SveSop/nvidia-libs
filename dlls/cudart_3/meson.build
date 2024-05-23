nvcuda_src = [
  'cudart.c',
]

arch_dir_prefix = target_machine.cpu_family() == 'x86_64' ? 'x86_64-' : 'i386-'

# Set different names based on architecture
lib_name = target_machine.cpu_family() == 'x86_64' ? 'cudart64_30_14.dll' : 'cudart32_30_14.dll'

install_dir_unix    = install_dir / arch_dir_prefix + 'unix'
install_dir_windows = install_dir / arch_dir_prefix + 'windows'

thread_dep = dependency('threads')


cudart_res_target = custom_target('cudart.res',
  output  : 'cudart.res',
  input   : 'cudart.rc',
  command : [ wrc, target_arch, '--nostdinc', '-I.', '-I'+meson.source_root()+'/include', '-D__WINESRC__', '-o', '@OUTPUT@', '@INPUT@' ],
  install : false)


cudart_dll = shared_library(lib_name, nvcuda_src,
  name_prefix         : '',
  dependencies        : [ thread_dep, lib_dl ],
  include_directories : include_path,
  objects             : 'cudart.spec',
  install             : true,
  install_dir         : install_dir_unix)


cudart_def_target = custom_target('cudart.def',
  output  : 'cudart.def',
  input   : 'cudart.spec',
  command : [ winebuild, target_arch, '-w', '--def', '-o', '@OUTPUT@', '-E', '@INPUT@' ],
  install : false)


cudart3_dll_target = custom_target(lib_name,
  output  : lib_name,
  input   : [ cudart_def_target, cudart_res_target ],
  command : [ winebuild, target_arch, '--dll', '--fake-module', '-o', '@OUTPUT@', '-E', '@INPUT@' ],
  install : true,
  install_dir : install_dir_windows)
