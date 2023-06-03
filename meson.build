project('CPPBDD', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3',
                     'cpp_std=c++20',
                     'buildtype=debugoptimized'])

gtest = subproject('gtest')
inja = subproject('inja')

subdir('test_execution')
subdir('translator')
