#include "cppbdd/task_manager.hpp"

namespace cppbdd {

std::array<std::string, 5> Task::task_names_({
    "Scenario:",
    "Given",
    "When",
    "Then",
    "And"
});

void Task::PrintMessage(void) const {
    switch (name_) {
    case TaskName::kScenario:
        std::cout << std::endl;
        break;
    case TaskName::kGiven:
        std::cout << std::endl;
        [[fallthrough]];
    case TaskName::kWhen:
    case TaskName::kThen:
    case TaskName::kAnd:
        std::cout << "  ";
        break;
    }
    std::cout << task_names_[name_] << ' ' << msg_ << std::endl;
}

void TaskManager::clear() {
    tasks_.clear();
}

void TaskManager::RunAll(void) {
    size_t exe_times = 1;
    for (const auto& task : tasks_) {
        size_t curr = task->GetMinReqExeTimes();
        // all multi-arg tasks must have the same number of test cases
        if (curr > 1) {
            exe_times = curr;
            break;
        }
    }

    for (size_t i = 0 ; i < exe_times; i++) {
        for (const auto& task : tasks_) {
            (*task)();
        }
    }
}

}  // namespace cppbdd
