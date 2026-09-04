#include <cstddef>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <stdexcept>

template<typename T>
class BlockingQueue {
    private:
        std::queue<T> queue_;
        std::size_t capacity_;

        std::mutex mutex_;

        std::condition_variable notFull_;
        std::condition_variable notEmpty_;

        /*size_t size() const {
            return queue_.size();
        }
        */

        bool isEmpty() const {
            return queue_.empty();
        }

        bool isFull() const {
            return queue_.size() == capacity_;
        }

    public:
        explicit BlockingQueue(size_t capacity) : capacity_(capacity) {
            if (capacity == 0) {
                throw std::invalid_argument("Capacity cannot be 0");
            }
        }

        void enqueue(const T& value) {
            std::unique_lock<std::mutex> ul(mutex_);

            notFull_.wait(ul, [this]{
                return !isFull();
            });

            queue_.push(value);

            ul.unlock();

            notEmpty_.notify_one();
        }

        T dequeue() {
            std::unique_lock<std::mutex> ul(mutex_);
            
            notEmpty_.wait(ul, [this]{
                return !isEmpty();
            });

            T value = queue_.front();
            queue_.pop();

            ul.unlock();

            notFull_.notify_one();

            return value;
        }
};