task_manager_test_source = files(
  'print_message_test.cpp',
  'operator_parenthesis_test.cpp',
  'add_task_test.cpp',
  'run_all_test.cpp')

task_manager_test = executable('task_manager_test',
  [task_manager_test_source, test_main],
  include_directories: inc,
  dependencies: test_deps,
  link_with: task_manager_lib)

test('Test the library task_manager', task_manager_test)
