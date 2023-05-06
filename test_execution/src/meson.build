main_source = files('cppbdd.cpp')

scenario_manager_source = files('cppbdd/ScenarioManager.cpp')
scenario_manager_lib = static_library('ScenarioManager',
  scenario_manager_source,
  include_directories: inc)
libs += scenario_manager_lib

task_manager_source = files('cppbdd/TaskManager.cpp')
task_manager_lib = static_library('TaskManager',
  task_manager_source,
  include_directories: inc)
libs += task_manager_lib
