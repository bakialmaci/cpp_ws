#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;  // Shared flag
int data = 0;        // Shared data

// Producer function
void producer(void) {
    std::this_thread::sleep_for(std::chrono::seconds(1));  // Simulate work
    std::lock_guard<std::mutex> lock(mtx);  // Lock the mutex
    data = 42;  // Produce the data
    ready = true;  // Set the flag to true
    std::cout << "Producer: Data produced.\n";
    cv.notify_one();  // Notify the consumer
}

// Consumer function
void consumer(void) {
    std::unique_lock<std::mutex> lock(mtx);  // Lock the mutex
    cv.wait(lock, [] { return ready; });  // Wait until ready is true
    std::cout << "Consumer: Data received: " << data << std::endl;
}

int main() {
    std::thread t1(producer);  // Producer thread
    std::thread t2(consumer);  // Consumer thread

    t1.join();
    t2.join();
    return 0;
}
