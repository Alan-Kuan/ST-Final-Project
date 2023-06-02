scenario_manager_test_source = files(
  'add_scenario_test.cpp',
  'operator_parenthesis_test.cpp',
  'run_all_test.cpp')

scenario_manager_test = executable('scenario_manager_test',
  [scenario_manager_test_source, test_main],
  include_directories: inc,
  dependencies: test_deps,
  link_with: [task_manager_lib, scenario_manager_lib])

test('Test the library scenario_manager', scenario_manager_test)
