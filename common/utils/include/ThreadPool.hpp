#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>

#pragma once

class ThreadPool {
public:
    ThreadPool(size_t num_threads);
    ~ThreadPool();

    // Enqueue a task
    template <class F, class... Args>
    auto enqueue(F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type> {
        using returnType = typename std::result_of<F(Args...)>::type;

        auto task = std::make_shared<std::packaged_task<returnType()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );

        std::future<returnType> res = task->get_future();
        {
            std::unique_lock<std::mutex> lock(_queue_mutex);

            // Don't allow enqueueing after stopping the pool
            if (_stop) throw std::runtime_error("enqueue on stopped ThreadPool");

            _tasks.emplace([task]() { (*task)(); });
        }
        _condition.notify_one();
        return res;
    }

private:
    std::vector<std::thread> _workers;
    std::queue<std::function<void()>> _tasks;

    std::mutex _queue_mutex;
    std::condition_variable _condition;
    bool _stop;
};
