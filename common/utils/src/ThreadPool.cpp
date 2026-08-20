/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** ThreadPool
*/

#include "ThreadPool.hpp"

ThreadPool::ThreadPool(size_t num_threads) : _stop(false) {
    for (size_t i = 0; i < num_threads; ++i) {
        _workers.emplace_back([this] {
            while (true) {
                std::function<void()> task;

                {
                    std::unique_lock<std::mutex> lock(_queue_mutex);
                    // Wait for a task to be available or for shutdown
                    _condition.wait(lock, [this] { return _stop || !_tasks.empty(); });

                    if (_stop && _tasks.empty()) return;

                    // Get the next task from the queue
                    task = std::move(_tasks.front());
                    _tasks.pop();
                }

                // Execute the task
                task();
            }
        });
    }
}

ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(_queue_mutex);
        _stop = true;
    }
    _condition.notify_all();
    for (std::thread &worker : _workers) {
        worker.join();
    }
}