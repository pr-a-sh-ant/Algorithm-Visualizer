#include "ThreadPool.h"

viz::thread::ThreadPool* viz::thread::ThreadPool::instance_ = nullptr;

void viz::thread::ThreadPool::thread_loop()
{
	while (true)
	{
		std::function<void()> job;
		{
			std::unique_lock<std::mutex> lock(this->queue_mutex_);
			this->mutex_condition_.wait(lock, [this]
			{
				return !this->jobs_.empty() || this->should_terminate_;
			});
			if (this->should_terminate_)
			{
				return;
			}
			job = jobs_.front();
			jobs_.pop();
		}
		job();
	}
}

viz::thread::ThreadPool& viz::thread::ThreadPool::initialize()
{
	if (instance_ != nullptr)
	{
		throw std::runtime_error("Thread pool already initialized");
	}

	instance_ = new ThreadPool();

	const auto num_threads = std::thread::hardware_concurrency();
	for (uint32_t i = 0; i < 3; i++)
	{
		instance_->threads_.emplace_back(std::thread(&ThreadPool::thread_loop, instance_));
	}

	return std::ref(*instance_);
}

viz::thread::ThreadPool& viz::thread::ThreadPool::get_instance()
{
	if (instance_ == nullptr)
	{
		throw std::runtime_error("Thread pool not initialized");
	}

	return std::ref(*instance_);
}

bool viz::thread::ThreadPool::is_initialized()
{
	return ThreadPool::instance_ != nullptr;
}

void viz::thread::ThreadPool::queue_job(std::function<void()> job)
{
	{
		std::unique_lock<std::mutex> lock(this->queue_mutex_);
		this->jobs_.push(job);
	}
	this->mutex_condition_.notify_one();
}

bool viz::thread::ThreadPool::busy()
{
	bool pool_busy;
	{
		std::unique_lock<std::mutex> lock(this->queue_mutex_);
		pool_busy = !this->jobs_.empty();
	}
	return pool_busy;
}

void viz::thread::ThreadPool::stop()
{
	{
		std::unique_lock<std::mutex> lock(this->queue_mutex_);
		this->should_terminate_ = true;
	}
	this->mutex_condition_.notify_all();

	for (auto& thread : this->threads_)
	{
		thread.join();
	}
	delete instance_;
	instance_ = nullptr;
}
