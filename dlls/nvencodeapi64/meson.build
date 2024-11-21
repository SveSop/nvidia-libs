nvencodeapi64_src = [
  '../nvencodeapi/nvencodeapi.c',
]

thread_dep = dependency('threads')


nvencodeapi64_dll = shared_library('nvencodeapi64.dll', nvencodeapi64_src,
  name_prefix         : '',
  dependencies        : [ thread_dep, lib_dl ],
  include_directories : include_path,
  objects             : '../nvencodeapi/nvencodeapi.spec',
  install             : true)
