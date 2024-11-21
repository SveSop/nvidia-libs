nvcuda_src = [
  'cufft.c',
]

thread_dep = dependency('threads')


cufft_dll = shared_library('cufft64_11.dll', nvcuda_src,
  name_prefix         : '',
  dependencies        : [ thread_dep, lib_dl ],
  include_directories : include_path,
  objects             : 'cufft.spec',
  install             : true)
