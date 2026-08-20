/*
** EPITECH PROJECT, 2024
** src
** File description:
** ThreadPool
*/

#include "ThreadPool.hpp"

ThreadPool::ThreadPool(size_t threads) : _stop(false), _tasks_left(0)
{
    for(size_t i = 0; i < threads; ++i)
        _workers.emplace_back(
            [this] {
                while (true) {
                    std::function<void()> task;

                    {
                        std::unique_lock<std::mutex> lock(this->_queue_mutex);
                        this->_condition.wait(lock, [this]{ return this->_stop || !this->_tasks.empty(); });
                        if(this->_stop && this->_tasks.empty())
                            return;
                        task = std::move(this->_tasks.front());
                        this->_tasks.pop();
                    }

                    task();
                    --_tasks_left;
                    _finished.notify_one();
                }
            }
        );
}

ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(_queue_mutex);
        _stop = true;
    }
    _condition.notify_all();
    for(std::thread &worker: _workers)
        worker.join();
}

void ThreadPool::wait()
{
    std::unique_lock<std::mutex> lock(_queue_mutex);
    _finished.wait(lock, [this] { return _tasks_left == 0; });
}
