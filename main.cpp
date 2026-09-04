#include "BlockingQueue.hpp"
#include <mutex>
#include <thread>
#include <iostream>

int main() {

BlockingQueue<int> queue(5);

std::mutex coutMutex;

std::thread producer([&queue, &coutMutex](){
    for (int i = 1; i <= 10; i++) {
        queue.enqueue(i);

        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << "Producer produced: " << i << "\n";
    }
});

std::thread consumer([&queue, &coutMutex](){
    for (int i = 1; i <= 10; i++) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        int value = queue.dequeue();
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << "Consumer consumed: " << value << "\n";
    }
});

producer.join();
consumer.join();

    return 0;
}