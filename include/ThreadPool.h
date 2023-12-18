#pragma once

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

namespace viz::thread
{
    // Singleton thread pool class for handling concurrent jobs
    class ThreadPool
    {
    private:
        bool should_terminate_ = false;            // Flag to stop threads from looking for jobs
        std::mutex queue_mutex_;                   // Mutex to prevent data races in the job queue
        std::condition_variable mutex_condition_;  // Condition variable for threads to wait on jobs or termination
        std::vector<std::thread> threads_;        // Collection of worker threads
        std::queue<std::function<void()>> jobs_;  // Queue to store jobs as functions
        static ThreadPool* instance_;              // Singleton instance pointer

        void thread_loop();  // Worker thread function

        ThreadPool() = default;  // Private default constructor

    public:
        // Initialize the thread pool singleton
        static ThreadPool& initialize();

        // Get the instance of the thread pool singleton
        static ThreadPool& get_instance();

        // Check if the thread pool is initialized
        static bool is_initialized();

        // Queue a job for execution
        void queue_job(std::function<void()> job);

        // Check if the thread pool is busy with jobs
        [[nodiscard]] bool busy();

        // Stop the thread pool and join threads
        void stop();
    };
}
