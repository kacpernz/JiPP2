#pragma once
#include "Tasks.hpp"
#include "TaskLogger.hpp"
#include <memory>
#include <vector>

class Executor {
public:
    void addTask(std::unique_ptr<Task> task);
    void runAll(TaskLogger& logger);
private:
    std::vector<std::unique_ptr<Task>> tasks;
};