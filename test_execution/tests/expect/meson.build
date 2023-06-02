expect_test_source = files(
  'expect_test.cpp',
  'expect_true_test.cpp',
  'expect_false_test.cpp',
  'expect_equal_test.cpp',
  'expect_not_equal_test.cpp',
  'expect_less_than_test.cpp',
  'expect_less_than_or_equal_test.cpp',
  'expect_greater_than_test.cpp',
  'expect_greater_than_or_equal_test.cpp',
  'show_expectation_test.cpp')

expect_test = executable('expect_test',
  [expect_test_source, test_main],
  include_directories: inc,
  dependencies: test_deps,
  link_with: [test_execution])

test('Test the library expect', expect_test)
