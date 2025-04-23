#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <semaphore>  // For std::counting_semaphore
#include <vector>
#include <atomic>
using namespace std;


// A mutex is a synchronization primitive 
// used to protect shared resources in multithreaded environments
// It ensures that only one thread can access a critical section of 
// code at a time, preventing race conditions.
std::mutex mtx;

// A condition variable is a synchronization primitive that allows threads to wait
// for a certain condition to be met before proceeding.
// It is often used in conjunction with a mutex to synchronize access to shared resources.
// It allows threads to wait for events or signals from other threads before proceeding, 
// which is useful when a thread must wait for a resource to become available or for 
// certain state changes.
//
// Waiting: A thread can wait on a condition variable until it is notified by another thread.
// Notification: A thread can notify one or all waiting threads that a condition has changed.
// Spurious Wakeup: Condition variables can wake up threads even if the condition they are waiting for has not changed.
// This is known as a spurious wakeup, and it is important to always check the condition in a loop after waking up.
// This is a common pattern to avoid issues with spurious wakeups.
std::condition_variable cv;
std::queue<int> dataQueue; // Shared data queue
bool dataReady = false; // Flag to indicate if data is ready

// A counting semaphore initialized to 3 (allows 3 threads concurrently)
// The template argument specifies the maximum number of threads that can acquire the semaphore at once.
std::counting_semaphore<3> semaphore(3);

void task(int id, int sleepTime) {
    // Wait (decrement) semaphore
    semaphore.acquire();
    std::cout << "Thread " << id << " is in the critical section." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(sleepTime)); // Simulate work
    std::cout << "Thread " << id << " is leaving the critical section." << std::endl;
    // Signal (increment) semaphore
    semaphore.release();
}

int test_semaphore() {
    std::vector<std::thread> threads;
    for (int i = 0; i < 5; ++i) {
        threads.push_back(thread(task, i, 1));
    }

    // Wait for all threads to finish
    for (auto& th : threads) {
        th.join();
    }

    return 0;
}


// A basic mutex teste case
void print_numbers(int num) {
    // Lock mutex before entering critical section
    mtx.lock();
    for (int i = 0; i < 5; ++i) {
        std::cout << "Thread " << num << ": " << i << std::endl;
    }
    // Unlock mutex after leaving critical section
    mtx.unlock();
}

void test_basic_mutex(){
    std::thread t1(print_numbers, 1);
    std::thread t2(print_numbers, 2);
    t1.join();
    t2.join();
    std::cout << "Done with basic mutex test\n" << std::endl;
}

// An example of prodcer/consumer in and multithreaded enviroment 
// with shared access to dataQueue
void producer() {
    std::this_thread::sleep_for(std::chrono::seconds(1));  // Simulate work
    
    // Lock the mutex before accessing shared data using std::lock_guard
    // This will automatically unlock the mutex when it goes out of scope
    // This is a RAII (Resource Acquisition Is Initialization) style of locking
    // which ensures that the mutex is always released even if an exception occurs
    // This is a good practice to avoid deadlocks and ensure proper resource management
    // std::lock_guard is a lightweight wrapper around std::mutex
    // that provides a convenient way to lock and unlock the mutex.
    {   std::lock_guard<std::mutex> lock(mtx);
        
        dataQueue.push(100);  // Produce data
        dataReady = true;
        std::cout << "Producer: Data produced." << std::endl;
    }
    // Notify one waiting consumer
    // This will wake up one thread that is waiting on the condition variable
    // The notify_one() function is used to wake up one waiting thread
    // If there are multiple threads waiting, only one will be notified
    // If no threads are waiting, the notification is lost
    // This is useful to avoid waking up all waiting threads when only one can proceed
    cv.notify_one();  // Notify one waiting consumer
}

void consumer() {
    // Lock the mutex before accessing shared data using std::unique_lock
    // std::unique_lock is a more flexible locking mechanism than std::lock_guard
    // It allows for more complex locking and unlocking patterns
    // It can be used to lock and unlock the mutex multiple times
    // It can also be used with condition variables
    // std::unique_lock is a lightweight wrapper around std::mutex
    // that provides a convenient way to lock and unlock the mutex.
    // Once the unique_lock is created, it locks the mutex
    // and keeps it locked until the unique_lock goes out of scope
    // or is explicitly unlocked
    // We can also defer the locking of the mutex until we need it using std::unique_lock
    // Here we will lock the mutex at initialization time
    std::unique_lock<std::mutex> lock(mtx);
    // Wait until data is available
    // The wait() function will automatically unlock the mutex and put the thread to sleep
    // until it is notified by another thread
    // The wait() function will also re-lock the mutex when it wakes up.
    // The wait function takes a predicate as an argument
    // With a predicate: The thread will block until pred() evaluates to true. 
    // It checks the condition after every wakeup automatically.
    // Predicate Checking: Always use a predicate with cv.wait(). 
    // This prevents spurious wakeups from causing incorrect behavior.
    cv.wait(lock, []{ return dataReady; });
    
    // Consume data
    std::cout << "Consumer: Data consumed: " << dataQueue.front() << std::endl;
    dataQueue.pop();
    dataReady = false;
}

int basic_producer_consumer_test() {
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();

    return 0;
}

void task_unique_lock(int id){
    // Example of using std::unique_lock
    // std::unique_lock<std::mutex> lock(mtx);         // Automatically locks the mutex at construction
    // std::unique_lock<std::mutex> lock(mtx, std::adopt_lock); // Adopts an already locked mutex
    // std::unique_lock<std::mutex> lock(mtx, std::defer_lock);  // Creates but doesn't lock
    // std::unique_lock<std::mutex> lock(mtx, std::try_to_lock); // Attempts to lock, returns immediately if not locked
    
    // Using std::unique_lock to manage the mutex
    std::unique_lock<std::mutex> lock(mtx, std::defer_lock);  // Create without locking
    std::cout << "Thread " << id << " attempting to lock..." << std::endl;
    
    // Manually lock the mutex later
    lock.lock();
    std::cout << "Thread " << id << " has locked the mutex." << std::endl;
    
    // Simulate some work
    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    // Unlock manually before going out of scope
    // This is optional as the unique_lock will automatically unlock when it goes out of scope
    std::cout << "Thread " << id << " is doing some work..." << std::endl;
    lock.unlock();
    std::cout << "Thread " << id << " has unlocked the mutex." << std::endl;
}

void test_unique_lock() {
    std::thread t1(task_unique_lock, 1);
    std::thread t2(task_unique_lock, 2);
    
    t1.join();
    t2.join();
}

std::atomic<int> counter(0);
void atomic_increment(int thread_id) {
    std::cout << "Thread " << thread_id << " incrementing counter.\n" << std::endl;
    for (int i = 0; i < 1000; ++i) {
        ++counter;
    }
}
void test_atomic() {
    vector<thread> threads;
    for (int i = 0; i < 5; ++i) {
        threads.push_back(std::thread(atomic_increment, i));
    }
    
    for (auto& th : threads) {
        th.join();
    }
    // Print the final value of the counter
    std::cout << "Final counter value: " << counter.load() << std::endl;
}

int main(int argc, char* argv[]) {
    if (argv[1] == nullptr) {
        std::cout << "Please provide a test case number." << std::endl;
        return 1;
    } else if (std::string(argv[1]) == "basic_mutex") {
        std::cout << "Running basic mutex test..." << std::endl;
        test_basic_mutex();
    } else if (std::string(argv[1]) == "basic_producer_consumer") {
        // Run the producer/consumer test
        // This test will produce data and consume it in a multithreaded environment
        // with shared access to dataQueue
        // The producer will produce data and notify the consumer
        // The consumer will wait for the data to be produced before consuming it
        // This is a simple example of a producer/consumer problem
        std::cout << "Running producer/consumer test..." << std::endl;
        basic_producer_consumer_test();
    } else if (std::string(argv[1]) == "semaphore") {
        std::cout << "Running semaphore test..." << std::endl;
        test_semaphore();
    } else if (std::string(argv[1]) == "unique_lock") {
        std::cout << "Running unique lock test..." << std::endl;
        test_unique_lock();
    } else if (std::string(argv[1]) == "atomic") {
        std::cout << "Running atomic test..." << std::endl;
        test_atomic();
    } 
    else {
        std::cout << "Invalid test case number." << std::endl;
    }


    return 0;
}
