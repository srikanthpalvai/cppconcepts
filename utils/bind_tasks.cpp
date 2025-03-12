#include <iostream>
#include <queue>
#include <functional>
#include <string>

// A simple Task class that takes a message and prints it
class Task {
public:
    void execute(const std::string& message) {
        std::cout << "Executing task: " << message << std::endl;
    }
};

int main() {
    std::queue<std::function<void()>> taskQueue;
    Task task;

    // Creating tasks with std::bind and adding them to the queue
    taskQueue.push(std::bind(&Task::execute, &task, "Task 1: Hello"));
    taskQueue.push(std::bind(&Task::execute, &task, "Task 2: World"));
    taskQueue.push(std::bind(&Task::execute, &task, "Task 3: Foo"));
    taskQueue.push(std::bind(&Task::execute, &task, "Task 4: Bar"));

    // Execute each task from the queue
    while (!taskQueue.empty()) {
        // Get the next task in the queue
        auto taskToExecute = taskQueue.front();

        // Execute the task
        taskToExecute();

        // Remove the task from the queue
        taskQueue.pop();
    }

    return 0;
}
