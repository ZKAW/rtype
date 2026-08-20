#include <queue>
#include <mutex>

template <typename T>
class DoubleBufferQueue {
public:
    void push(const T& item) {
        std::lock_guard<std::mutex> lock(_mutex);
        _back_buffer.push(item);
    }

    std::optional<std::queue<T>> swapAndGet() {
        std::unique_lock<std::mutex> lock(_mutex, std::try_to_lock);
        if (!lock.owns_lock()) {
            // lock couldn't be acquired, return empty optional to avoid blocking
            return std::nullopt;
        }

        std::swap(_front_buffer, _back_buffer);
        std::queue<T> temp = std::move(_front_buffer);
        _front_buffer = std::queue<T>();
        return temp;
    }

private:
    std::queue<T> _front_buffer;
    std::queue<T> _back_buffer;
    std::mutex _mutex;
};
