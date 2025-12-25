project('nvidia-libs', ['c'], version: 'v1.0.0', license: 'mixed')

nvlibs_version = vcs_tag(
  command: ['git', 'describe', '--always', '--tags', '--long', '--dirty=+'],
  input:  'version.in',
  output: 'version')
