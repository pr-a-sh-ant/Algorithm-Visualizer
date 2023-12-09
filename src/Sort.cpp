#include "Sort.h"
#include "State.h"

void viz::sort::Sort::swap(const size_t index_first, const size_t index_second)
{
	std::swap(sort_space_->box_heights[index_first], sort_space_->box_heights[index_second]);
}

viz::sort::Sort::Sort(SortSpace *sort_space, const float step_delay)
	: sort_space_(sort_space), step_delay_(step_delay), step_clock_(0.0f)
{
}

void viz::sort::Sort::update(const float delta_time_sec)
{
	if (State::get_state_instance().sort.visualizer_mode == sort_visualizer_mode::sorting)
	{
		this->step_clock_ += delta_time_sec;
		if (this->step_clock_ >= this->step_delay_)
		{
			this->step_clock_ -= this->step_delay_;
			this->run_sort_step();
		}
	}
}

bool viz::sort::Sort::is_sort_complete() const
{
	return State::get_state_instance().sort.visualizer_mode == sort_visualizer_mode::completed;
}

bool viz::sort::Sort::is_sort_running() const
{
	return State::get_state_instance().sort.visualizer_mode == sort_visualizer_mode::sorting;
}

float viz::sort::Sort::get_step_delay() const
{
	return this->step_delay_;
}

void viz::sort::Sort::set_step_delay(const float step_delay)
{
	this->step_delay_ = step_delay;
}

void viz::sort::Sort::reset()
{
	this->step_clock_ = 0.0f;
	State::get_state_instance().sort.visualizer_mode = sort_visualizer_mode::none;
	this->sort_space_->randomize();
}

void viz::sort::Sort::start_sort()
{
	this->step_clock_ = 0.0f;
	State::get_state_instance().sort.visualizer_mode = sort_visualizer_mode::sorting;
}

viz::sort::BubbleSort::BubbleSort(viz::sort::SortSpace *sort_space, const float step_delay)
	: Sort(sort_space, step_delay), outer_loop_index_(0), inner_loop_index_(0)
{
}

void viz::sort::BubbleSort::run_sort_step()
{
	if (this->outer_loop_index_ < this->sort_space_->box_heights.size())
	{
		if (this->inner_loop_index_ < this->sort_space_->box_heights.size() - this->outer_loop_index_ - 1)
		{
			if (this->sort_space_->box_heights[this->inner_loop_index_] > this->sort_space_->box_heights[this->inner_loop_index_ + 1])
			{
				this->swap(this->inner_loop_index_, this->inner_loop_index_ + 1);
			}
			this->inner_loop_index_++;
		}
		else
		{
			this->outer_loop_index_++;
			this->inner_loop_index_ = 0;
		}
	}
	else
	{
		State::get_state_instance().sort.visualizer_mode = sort_visualizer_mode::completed;
	}
}

void viz::sort::BubbleSort::reset()
{
	Sort::reset();
	this->outer_loop_index_ = 0;
	this->inner_loop_index_ = 0;
}

void viz::sort::BubbleSort::start_sort()
{
	Sort::start_sort();
	this->outer_loop_index_ = 0;
	this->inner_loop_index_ = 0;
}

viz::sort::SelectionSort::SelectionSort(viz::sort::SortSpace* sort_space, const float step_delay)
	: Sort(sort_space, step_delay), outer_loop_index_(0), inner_loop_index_(0), min_index_(0)
{
}

void viz::sort::SelectionSort::run_sort_step()
{
	if (this->outer_loop_index_ < this->sort_space_->box_heights.size() - 1)
	{
		if (this->inner_loop_index_ < this->sort_space_->box_heights.size())
		{
			if (this->sort_space_->box_heights[this->inner_loop_index_] < this->sort_space_->box_heights[min_index_])
			{
				min_index_ = this->inner_loop_index_;
			}
			this->inner_loop_index_++;
		}
		else
		{
			if (min_index_ != this->outer_loop_index_) {
				this->swap(min_index_, this->outer_loop_index_);
			}
			this->outer_loop_index_++;
			this->inner_loop_index_ = this->outer_loop_index_ + 1;
			min_index_ = this->outer_loop_index_;
		}
	}
	else
	{
		State::get_state_instance().sort.visualizer_mode = sort_visualizer_mode::completed;
	}
}

void viz::sort::SelectionSort::reset()
{
	Sort::reset();
	this->outer_loop_index_ = 0;
	this->inner_loop_index_ = 0;
	this->min_index_ = 0;
}

void viz::sort::SelectionSort::start_sort()
{
	Sort::start_sort();
	this->outer_loop_index_ = 0;
	this->inner_loop_index_ = 0;
	this->min_index_ = 0;
}

viz::sort::MergeSort::MergeSort(viz::sort::SortSpace* sort_space, const float step_delay)
	: Sort(sort_space, step_delay), left_index_(0), right_index_(0), merge_index_(0)
{
}

void viz::sort::MergeSort::merge(size_t left, size_t middle, size_t right) {
	size_t left_size = middle - left + 1;
	size_t right_size = right - middle;

	// Create temporary arrays for left and right subarrays
	std::vector<float> left_array(left_size);
	std::vector<float> right_array(right_size);

	// Copy data to temporary arrays
	for (size_t i = 0; i < left_size; ++i) {
		left_array[i] = sort_space_->box_heights[left + i];
	}
	for (size_t j = 0; j < right_size; ++j) {
		right_array[j] = sort_space_->box_heights[middle + 1 + j];
	}

	// Merge the temporary arrays back into the main array
	size_t i = 0, j = 0, k = left;
	while (i < left_size && j < right_size) {
		if (left_array[i] <= right_array[j]) {
			sort_space_->box_heights[k] = left_array[i];
			i++;
		}
		else {
			sort_space_->box_heights[k] = right_array[j];
			j++;
		}
		k++;
	}

	// Copy the remaining elements of left_array, if any
	while (i < left_size) {
		sort_space_->box_heights[k] = left_array[i];
		i++;
		k++;
	}

	// Copy the remaining elements of right_array, if any
	while (j < right_size) {
		sort_space_->box_heights[k] = right_array[j];
		j++;
		k++;
	}
}

void viz::sort::MergeSort::run_sort_step() {
	size_t array_size = sort_space_->box_heights.size();

	if (merge_index_ < array_size - 1) {
		size_t middle = merge_index_;
		size_t right = std::min(merge_index_ + 2 * right_index_, array_size - 1);
		merge(left_index_, middle, right);
		merge_index_ = right + 1;
	}
	else {
		State::get_state_instance().sort.visualizer_mode = sort_visualizer_mode::completed;
	}
}

void viz::sort::MergeSort::reset() {
	Sort::reset();
	left_index_ = 0;
	right_index_ = 0;
	merge_index_ = 0;
}

void viz::sort::MergeSort::start_sort() {
	Sort::start_sort();
	left_index_ = 0;
	right_index_ = 1;
	merge_index_ = 0;
}