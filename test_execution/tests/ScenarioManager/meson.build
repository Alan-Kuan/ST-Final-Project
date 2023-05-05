test_scenario_manager_source = files('test_ScenarioManager.cpp')

test_scenario_manager = executable('test_ScenarioManager',
  [test_scenario_manager_source, test_main],
  include_directories: inc,
  dependencies: test_deps,
  link_with: scenario_manager_lib)

test('test ScenarioManager', test_scenario_manager)
