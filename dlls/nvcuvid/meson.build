nvcuvid_src = [
  'nvcuvid.c',
]

thread_dep = dependency('threads')


nvcuvid_dll = shared_library('nvcuvid.dll', nvcuvid_src,
  name_prefix         : '',
  dependencies        : [ thread_dep, lib_dl ],
  include_directories : include_path,
  objects             : 'nvcuvid.spec',
  install             : true)
