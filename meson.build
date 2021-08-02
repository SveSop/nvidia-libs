project('nvidia-libs', ['c'])

cpu_family = target_machine.cpu_family()

include_path = include_directories('./include')

lib_dl      = declare_dependency(link_args: [ '-ldl' ])

winebuild   = find_program('winebuild')
winegcc     = find_program('winegcc')
widl        = find_program('widl')
wrc         = find_program('wrc')

target_arch = cpu_family == 'x86_64' ? '-m64' : '-m32'

def_generator = generator(winebuild,
  output    : [ '@BASENAME@.def' ],
  arguments : [ '-w', ' --def', '--export', '@INPUT@', '-o', '@OUTPUT@' ])

idl_generator = generator(widl,
  output    : [ '@BASENAME@.h' ],
  arguments : [ target_arch, '-o', '@OUTPUT@', '-D__WINESRC__', '@EXTRA_ARGS@', '@INPUT@' ])

install_dir = get_option('libdir') / 'wine'

subdir('dlls')
