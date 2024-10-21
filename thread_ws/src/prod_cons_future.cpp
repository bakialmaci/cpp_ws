#include <future>
#include <thread>
#include <iostream>

int produce() {
    std::this_thread::sleep_for(std::chrono::seconds(1));  // Simulate producing data
    return 42;
}

void consume(std::future<int>& fut) {
    int result = fut.get();  // Wait for the result
    std::cout << "Consumed: " << result << std::endl;
}

int main() {
    std::future<int> fut = std::async(std::launch::async, produce);  // Async producer
    consume(fut);  // Consumer waits for the result
    return 0;
}
