#pragma once

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

	class MergeSort : public Sort {
	private:
		size_t left_index_;   // Index for the left subarray
		size_t right_index_;  // Index for the right subarray
		size_t merge_index_;  // Index for merging the subarrays

		// Merge function for merging two subarrays
		void merge(size_t left, size_t middle, size_t right);

	public:
		MergeSort(viz::sort::SortSpace* sort_space, const float step_delay);

		void run_sort_step() override;
		void reset() override;
		void start_sort() override;
	};
}