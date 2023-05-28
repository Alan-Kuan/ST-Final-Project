#ifndef SCENARIO_MANAGER_HPP
#define SCENARIO_MANAGER_HPP

#include <any>
#include <map>
#include <string>
#include <memory>
#include "cppbdd/TaskManager.hpp"

namespace cppbdd {

class ScenarioTask : public Task {
public:
    typedef map<string, any> Context;
    typedef function<void(Context&)> Callable;

    ScenarioTask(const string& msg, Callable callback)
        : Task(TaskName::SCENARIO, msg),
          callback_(callback) {}

    void operator() (Context& context);

protected:
    Context context_;
    Callable callback_;

// disable these pure virtual functions inherited from Task
private:
    void operator() (void) {}
    size_t getMinReqExeTimes(void) const { return 0; }
};

typedef unique_ptr<ScenarioTask> ScenarioTaskUniquePtr;


class ScenarioManager {
public:
    bool addTaskToCurrStmtManager(CallableTask* const task) {
        return stmt_manager_.addTask(task);
    }

    template<typename T>
    bool addTaskToCurrStmtManager(SingleArgCallableTask<T>* const task) {
        return stmt_manager_.addTask(task);
    }

    bool addScenario(ScenarioTask* const scenario);
    void runAll(void);

protected:
    TaskManager stmt_manager_;
    vector<ScenarioTaskUniquePtr> scenarios_;
};

}  // namespace: cppbdd

#endif  // SCENARIO_MANAGER_HPP
