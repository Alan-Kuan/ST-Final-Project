cppbdd_test_source = files(
  'Title_test.cpp',
  'UserStory_test.cpp')

cppbdd_test = executable('cppbdd_test',
  [cppbdd_test_source, test_main],
  include_directories: inc,
  dependencies: test_deps,
  link_with: [test_execution])

test('Test the library cppbdd', cppbdd_test)
