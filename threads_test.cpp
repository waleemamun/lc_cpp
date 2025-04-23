#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>
#include <atomic>

class ThreadPool {
public:
    ThreadPool(size_t numThreads);
    ~ThreadPool();

    void enqueueJob(std::function<void()> job);

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> jobs;

    std::mutex queueMutex;
    std::condition_variable condition;
    std::atomic<bool> stop;

    void workerLoop(int id);
};

ThreadPool::ThreadPool(size_t numThreads) : stop(false) {
    for (size_t i = 0; i < numThreads; ++i) {
        workers.emplace_back(&ThreadPool::workerLoop, this, i);
    }
}

ThreadPool::~ThreadPool() {
    stop = true;
    condition.notify_all(); // Wake up all threads
    for (auto& thread : workers) {
        if (thread.joinable()) {
            thread.join(); // Wait for all threads to finish
        }
    }
}

void ThreadPool::enqueueJob(std::function<void()> job) {
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        jobs.push(std::move(job));
    }
    condition.notify_one();
}

void ThreadPool::workerLoop(int id) {

    std::cout<<"\n Thread id: "<<id<<std::endl;
    while (true) {
        std::function<void()> job;
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            condition.wait(lock, [this]() { return stop || !jobs.empty(); });

            if (stop && jobs.empty())
                return;

            job = std::move(jobs.front());
            jobs.pop();
        }
        job();
    }
}

int main() {
    ThreadPool pool(4); // 4 worker threads

    for (int i = 1; i <= 10; ++i) {
        pool.enqueueJob([i]() {
            std::cout << "Processing job " << i 
                      << " in thread " << std::this_thread::get_id() << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        });
    }

    std::this_thread::sleep_for(std::chrono::seconds(4)); // Let jobs finish
    std::cout << "Main thread exiting.\n";
    return 0;
}
