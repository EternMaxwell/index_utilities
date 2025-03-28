#pragma once

#include <condition_variable>
#include <deque>
#include <mutex>
#include <optional>

namespace index::concurrent {
template <typename T>
struct conqueue {
   private:
    std::deque<T> queue;
    mutable std::mutex mutex;
    std::condition_variable cv;

   public:
    conqueue()                           = default;
    conqueue(const conqueue&)            = delete;
    conqueue(conqueue&&)                 = delete;
    conqueue& operator=(const conqueue&) = delete;
    conqueue& operator=(conqueue&&)      = delete;
    ~conqueue()                          = default;

    template <typename... Args>
    void emplace(Args&&... args) {
        std::lock_guard lock(mutex);
        queue.emplace_back(std::forward<Args>(args)...);
        cv.notify_one();
    }

    std::optional<T> try_pop() {
        std::lock_guard lock(mutex);
        if (queue.empty()) return std::nullopt;
        T value = std::move(queue.front());
        queue.pop_front();
        return std::move(value);
    }

    T pop() {
        std::lock_guard lock(mutex);
        cv.wait(lock, [this] { return !queue.empty(); });
        T value = std::move(queue.front());
        queue.pop_front();
        return std::move(value);
    }
};
}  // namespace index::concurrent