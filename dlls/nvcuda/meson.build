nvcuda_src = [
  'internal.c',
  'nvcuda.c',
  'function_mappings.c',
  'encryption.c',
]

thread_dep = dependency('threads')


nvcuda_dll = shared_library('nvcuda.dll', nvcuda_src,
  name_prefix         : '',
  dependencies        : [ thread_dep, lib_dl ],
  include_directories : include_path,
  objects             : 'nvcuda.spec',
  install             : true)
