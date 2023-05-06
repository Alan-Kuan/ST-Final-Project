#include "cppbdd/TaskManager.hpp"

namespace cppbdd {

void Task::printMessage(void) const {

}

template<typename T>
bool TaskManager::addTask(const std::string& msg, const T& callback) {
    return true;
}

void TaskManager::runAll(void) {

}

}  // namespace: cppbdd
