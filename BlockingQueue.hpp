#include <cstddef>
#include <queue>
#include <mutex>
#include <condition_variable>

template<typename T>
class BlockingQueue {
    private:
        std::queue<T> queue_;
        size_t capacity_;

    public:
        explicit BlockingQueue(size_t capacity) : capacity_(capacity) {}

        void enqueue(const T& value) {
            if (isFull()) {
                return;
            }

            queue_.push(value);
        }

        T dequeue();

        size_t size() const {
            return queue_.size();
        }

        bool isEmpty() const {
            return queue_.size() == 0;
        }

        bool isFull() const {
            return queue_.size() == capacity_;
        }
};