main_sources = files('cppbdd/cppbdd.cpp', 'cppbdd/expect.cpp')

task_manager_source = files('cppbdd/task_manager.cpp')
task_manager_lib = static_library('task_manager',
  task_manager_source,
  include_directories: inc)
libs += task_manager_lib

scenario_manager_source = files('cppbdd/scenario_manager.cpp')
scenario_manager_lib = static_library('scenario_manager',
  scenario_manager_source,
  include_directories: inc)
libs += scenario_manager_lib
