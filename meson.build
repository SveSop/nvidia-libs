project('nvidia-libs', ['c'], version: 'v0.8.1', license: 'mixed')

include_path = include_directories('./include')

lib_dl      = meson.get_compiler('c').find_library('dl')

winebuild   = find_program('winebuild')
winegcc     = find_program('winegcc')
wrc         = find_program('wrc')

target_arch = target_machine.cpu_family() == 'x86_64' ? '-m64' : '-m32'


nvlibs_version = vcs_tag(
  command: ['git', 'describe', '--always', '--tags', '--long', '--dirty=+'],
  input:  'version.in',
  output: 'version')

subdir('dlls')
