expect_test_source = files(
  'expect_test.cpp',
  'expect_true_test.cpp',
  'expect_false_test.cpp',
  'expect_eq_test.cpp',
  'expect_ne_test.cpp',
  'expect_lt_test.cpp',
  'expect_le_test.cpp',
  'expect_gt_test.cpp',
  'expect_ge_test.cpp')

expect_test = executable('expect_test',
  [expect_test_source, test_main],
  include_directories: inc,
  dependencies: test_deps,
  link_with: [test_execution])

test('Test the library expect', expect_test)
