#include "BlockingQueue.hpp"
#include <iostream>

int main() {

BlockingQueue<int> obj1(3);

obj1.enqueue(5);
obj1.enqueue(9);
obj1.enqueue(1);

std::cout << obj1.size();


    return 0;
}