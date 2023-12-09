#pragma once

#include <functional>

#include "SortSpace.h"

namespace viz::sort
{
	class Sort
	{
	protected:
		viz::sort::SortSpace* sort_space_; // Pointer to the sort space (not owned)
		float step_delay_; // The delay between each step in seconds
		float step_clock_; // The clock for the current step

		// Swaps the values at the given indices
		void swap(const size_t index_first, const size_t index_second);
	public:
		Sort(viz::sort::SortSpace* sort_space, const float step_delay);
		virtual ~Sort() = default;

		// Performs a single step of the sort
		virtual void run_sort_step() = 0;
		// Updates the sort step by step
		void update(const float delta_time_sec);

		// Returns true if the sort is completed
		[[nodiscard]]
		bool is_sort_complete() const;
		[[nodiscard]]
		bool is_sort_running() const;
		[[nodiscard]]
		float get_step_delay() const;

		// Setters
		void set_step_delay(const float step_delay);

		// Resets the sort
		virtual void reset();
		// Starts the sort
		virtual void start_sort();
	};

	class BubbleSort : public Sort
	{
	private:
		size_t outer_loop_index_; // The index of the outer loop
		size_t inner_loop_index_; // The index of the inner loop

	public:
		BubbleSort(viz::sort::SortSpace* sort_space, const float step_delay);

		void run_sort_step() override;
		void reset() override;
		void start_sort() override;
	};;

	class SelectionSort: public Sort
	{
	private:
		size_t outer_loop_index_; // The index of the outer loop
		size_t inner_loop_index_; // The index of the inner loop
		size_t min_index_; // The index of the minimum value
	public:
		SelectionSort(viz::sort::SortSpace* sort_space, const float step_delay);

		void run_sort_step() override;
		void reset() override;
		void start_sort() override;
	};

	class QuickSort: public Sort
	{
	private:
		std::vector<std::function<void()>> actions_;
		size_t current_action_index_;
		std::vector<int> array_copy_;
		bool is_base_sort_running_;

		int partition(const int low, const int high);
		void quick_sort(const int low, const int high);

	public:
		QuickSort(viz::sort::SortSpace* sort_space, const float step_delay);

		void run_sort_step() override;
		void reset() override;
		void start_sort() override;
	};

	class MergeSort : public Sort {
	private:
		std::vector<std::function<void()>> actions_;
		size_t current_action_index_;
		std::vector<int> array_copy_;
		bool is_base_sort_running_;

		void merge(const int left, const int middle, const int right);
		void merge_sort(const int left, const int right);

	public:
		MergeSort(viz::sort::SortSpace* sort_space, const float step_delay);

		void run_sort_step() override;
		void reset() override;
		void start_sort() override;
	};

	class RadixSort : public Sort {
	private:
		std::vector<std::function<void()>> actions_;
		size_t current_action_index_;
		std::vector<int> array_copy_;
		bool is_base_sort_running_;

		int get_max() const;
		void count_sort(int exp);

	public:
		RadixSort(viz::sort::SortSpace* sort_space, const float step_delay);

		void run_sort_step() override;
		void reset() override;
		void start_sort() override;
	};

	class BogoSort : public Sort
	{
	private:
		[[nodiscard]]
		bool is_sorted() const;

	public:
		BogoSort(viz::sort::SortSpace* sort_space, const float step_delay);

		void run_sort_step() override;
		void reset() override;
		void start_sort() override;
	};
}