#pragma once
#include <condition_variable>
#include <functional>
#include <queue>
#include <thread>

namespace viz::thread
{
	// Singleton thread pool class
	class ThreadPool
	{
	private:
		bool should_terminate_ = false;           // Tells threads to stop looking for jobs
		std::mutex queue_mutex_;                  // Prevents data races to the job queue
		std::condition_variable mutex_condition_; // Allows threads to wait on new jobs or termination 
		std::vector<std::thread> threads_;
		std::queue<std::function<void()>> jobs_;
		static ThreadPool* instance_;

		void thread_loop();

		ThreadPool() = default;

	public:
		static ThreadPool& initialize();
		static ThreadPool& get_instance();
		static bool is_initialized();

		void queue_job(std::function<void()> job);
		void stop();
		[[nodiscard]]
		bool busy();
	};
}
