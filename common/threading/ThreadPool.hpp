/*
** EPITECH PROJECT, 2024
** bstheplazza
** File description:
** ThreadPool
*/

#pragma once

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>
#include <atomic>
#include <chrono>

class ThreadPool {
    public:
        ThreadPool(size_t);
        ~ThreadPool();

        template<class F, class... Args>
        auto enqueue(F&& f, Args&&... args) -> std::future<typename std::invoke_result<F, Args...>::type>
        {
            using return_type = typename std::invoke_result<F, Args...>::type;

            auto task = std::make_shared<std::packaged_task<return_type()>>(
                std::bind(std::forward<F>(f), std::forward<Args>(args)...)
            );

            std::future<return_type> res = task->get_future();
            {
                std::unique_lock<std::mutex> lock(_queue_mutex);

                if(_stop)
                    throw std::runtime_error("enqueue on stopped ThreadPool");

                _tasks.emplace([task, this](){
                    _has_executed = true;
                    ++_working_threads;
                    (*task)();
                    --_working_threads;
                    _last_stop_time = std::chrono::steady_clock::now();
                });
                ++_tasks_left;
            }
            _condition.notify_one();
            return res;
        }

        double getIdlingTime() const {
            if (!_has_executed) return 0.0;
            auto now = std::chrono::steady_clock::now();
            auto idling_time = std::chrono::duration_cast<std::chrono::seconds>(now - _last_stop_time);
            return idling_time.count();
        }

        void wait();
        int getWorkingCooks() const { return _working_threads; }
        int getOrderablePizzaCount() const { return (_workers.size() * 2) - _tasks_left; }

    private:
        std::vector<std::thread> _workers;
        std::queue<std::function<void()>> _tasks;
        std::mutex _queue_mutex;
        std::condition_variable _condition;
        bool _stop;
        std::condition_variable _finished;
        std::atomic<size_t> _tasks_left;
        std::atomic<int> _working_threads = 0;
        std::chrono::time_point<std::chrono::steady_clock> _last_stop_time = std::chrono::steady_clock::now();
        bool _has_executed = false;
};
