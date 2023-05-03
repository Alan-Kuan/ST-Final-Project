project('translator', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3',
                     'cpp_std=c++17',
                     'buildtype=debugoptimized'])

sources = []
# Include path
inc = include_directories('include')

# Subdirectories
subdir('src')

# Dependencies
yaml_dep = dependency('yaml-cpp', required : true)

# Executable
exe = executable(
  'translator',
  sources,
  install : true,
  include_directories : inc,
  dependencies : [yaml_dep]
)
