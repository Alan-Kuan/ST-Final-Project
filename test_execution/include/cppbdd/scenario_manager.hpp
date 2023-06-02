#ifndef CPPBDD_SCENARIO_MANAGER_HPP_
#define CPPBDD_SCENARIO_MANAGER_HPP_

#include <any>
#include <unordered_map>
#include <string>
#include <memory>
#include "cppbdd/task_manager.hpp"

namespace cppbdd {

class ScenarioTask : public Task {
public:
    typedef std::unordered_map<std::string, std::any> Context;
    typedef std::function<void(Context&)> Callable;

    ScenarioTask(const std::string& msg, Callable callback)
        : Task(TaskName::kScenario, msg),
          callback_(callback) {}

    void operator() (Context& context);

protected:
    Context context_;
    Callable callback_;

// disable these pure virtual functions inherited from Task
private:
    void operator() (void) {}
    size_t GetMinReqExeTimes(void) const { return 0; }
};

typedef std::unique_ptr<ScenarioTask> ScenarioTaskUniquePtr;


class ScenarioManager {
public:
    bool AddTaskToCurrStmtManager(CallableTask* const task) {
        return stmt_manager_.AddTask(task);
    }

    template<typename T>
    bool AddTaskToCurrStmtManager(SingleArgCallableTask<T>* const task) {
        return stmt_manager_.AddTask(task);
    }

    bool AddScenario(ScenarioTask* const scenario);
    void RunAll(void);

protected:
    TaskManager stmt_manager_;
    std::vector<ScenarioTaskUniquePtr> scenarios_;
};

}  // namespace cppbdd

#endif  // CPPBDD_SCENARIO_MANAGER_HPP_
