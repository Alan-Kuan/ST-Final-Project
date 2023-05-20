libs = []
inc = [include_directories('include')]

subdir('src')

test_execution = library('cppbdd',
  main_sources,
  include_directories: inc,
  link_with: libs)

subdir('tests')
