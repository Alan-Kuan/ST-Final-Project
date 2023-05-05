libs = []
inc = [include_directories('include')]

subdir('src')

test_execution = library('cppbdd',
  main_source,
  include_directories: inc,
  link_with: libs)

subdir('tests')
