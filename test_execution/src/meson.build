main_source = files('cppbdd.cpp')

task_manager_source = files('cppbdd/TaskManager.cpp')
task_manager_lib = static_library('TaskManager',
  task_manager_source,
  include_directories: inc)
libs += task_manager_lib
