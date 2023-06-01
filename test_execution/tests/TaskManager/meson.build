task_manager_test_source = files(
  'printMessage_test.cpp',
  'operator_parenthesis_test.cpp',
  'addTask_test.cpp',
  'runAll_test.cpp')

task_manager_test = executable('TaskManager_test',
  [task_manager_test_source, test_main],
  include_directories: inc,
  dependencies: test_deps,
  link_with: task_manager_lib)

test('Test the library TaskManager', task_manager_test)
