nvencodeapi_src = [
  'nvencodeapi.c',
]

thread_dep = dependency('threads')


nvencodeapi_dll = shared_library('nvencodeapi.dll', nvencodeapi_src,
  name_prefix         : '',
  dependencies        : [ thread_dep, lib_dl ],
  include_directories : include_path,
  objects             : 'nvencodeapi.spec',
  install             : true)
