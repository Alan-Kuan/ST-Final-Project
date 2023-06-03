sources = []
# Include path
inc = include_directories('include')

# Subdirectories
subdir('src')

# Dependencies
yaml_dep = dependency('yaml-cpp', required : true)
inja_dep = inja.get_variable('inja_dep')

# Executable
exe = executable(
  'translator',
  sources,
  install : true,
  include_directories : inc,
  dependencies : [yaml_dep, inja_dep]
)
