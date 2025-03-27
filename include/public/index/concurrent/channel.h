#include <memory>
#include <optional>
#include <tuple>

#include "conqueue.h"

namespace index::channel {
template <typename T>
struct Sender {
    using conqueue = index::concurrent::conqueue<T>;

   private:
    std::shared_ptr<conqueue> queue;

   public:
    Sender(const std::shared_ptr<conqueue>& queue) : queue(queue) {}
    Sender()                         = default;
    Sender(const Sender&)            = default;
    Sender(Sender&&)                 = default;
    Sender& operator=(const Sender&) = default;
    Sender& operator=(Sender&&)      = default;
    ~Sender()                        = default;

    operator bool() { return queue.operator bool(); }
    bool operator!() { return !queue; }

    template <typename... Args>
    void send(Args&&... args) {
        if (!queue) return;
        queue->emplace(std::forward<Args>(args)...);
    }
};
template <typename T>
struct Receiver {
    using conqueue = index::concurrent::conqueue<T>;

   private:
    std::shared_ptr<conqueue> queue;

   protected:
    Receiver(const std::shared_ptr<conqueue>& queue) : queue(queue) {}

   public:
    Receiver(const Receiver&)            = default;
    Receiver(Receiver&&)                 = default;
    Receiver& operator=(const Receiver&) = default;
    Receiver& operator=(Receiver&&)      = default;
    ~Receiver()                          = default;

    std::optional<T> try_receive() { return queue->try_pop(); }

    T receive() { return queue->pop(); }
};

template <typename T>
std::tuple<Sender<T>, Receiver<T>> make_channel() {
    auto queue = std::make_shared<index::concurrent::conqueue<T>>();
    return {Sender<T>(queue), Receiver<T>(queue)};
}
}  // namespace index::channel