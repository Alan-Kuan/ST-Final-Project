scenario_manager_test_source = files(
  'addScenario_test.cpp',
  'operator_parenthesis_test.cpp',
  'runAll_test.cpp')

scenario_manager_test = executable('ScenarioManager_test',
  [scenario_manager_test_source, test_main],
  include_directories: inc,
  dependencies: test_deps,
  link_with: [task_manager_lib, scenario_manager_lib])

test('Test the library ScenarioManager', scenario_manager_test)
