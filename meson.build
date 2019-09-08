project('CGDS', 'c',
  version : '0.1',
  default_options : ['warning_level=3'])

inc_dir = include_directories('include')

subdir('include')
subdir('src')
subdir('test')

pkg_mod = import('pkgconfig')
pkg_mod.generate(
  name : 'cgds',
  filebase : 'cgds',
  description : 'C generic data structures',
  subdirs : 'cgds',
  libraries : shlib,
  version : '0.1',
)
