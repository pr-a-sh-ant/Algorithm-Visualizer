#include "Sort.h"
#include "State.h"
#include "ThreadPool.h"

void viz::sort::Sort::swap(const size_t index_first, const size_t index_second)
{
	std::swap(sort_space_->box_heights[index_first], sort_space_->box_heights[index_second]);
}

viz::sort::Sort::Sort(SortSpace* sort_space, const float step_delay)
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

viz::sort::BubbleSort::BubbleSort(SortSpace* sort_space, const float step_delay)
	: Sort(sort_space, step_delay), outer_loop_index_(0), inner_loop_index_(0)
{
}

void viz::sort::BubbleSort::run_sort_step()
{
	if (this->outer_loop_index_ < this->sort_space_->box_heights.size())
	{
		if (this->inner_loop_index_ < this->sort_space_->box_heights.size() - this->outer_loop_index_ - 1)
		{
			if (this->sort_space_->box_heights[this->inner_loop_index_] > this->sort_space_->box_heights[this->
				inner_loop_index_ + 1])
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

viz::sort::SelectionSort::SelectionSort(SortSpace* sort_space, const float step_delay)
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
			if (min_index_ != this->outer_loop_index_)
			{
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

int viz::sort::QuickSort::partition(const int low, const int high)
{
	const int pivot = this->array_copy_[high];
	int i = low - 1;

	for (int j = low; j < high; j++)
	{
		if (this->array_copy_[j] < pivot)
		{
			i++;
			std::swap(this->array_copy_[i], this->array_copy_[j]);
			this->actions_.emplace_back([this, i, j]()
			{
				this->swap(i, j);
			});
		}
	}

	std::swap(this->array_copy_[i + 1], this->array_copy_[high]);
	this->actions_.emplace_back([this, i, high]()
	{
		this->swap(i + 1, high);
	});

	return i + 1;
}

void viz::sort::QuickSort::quick_sort(const int low, const int high)
{
	if (low < high)
	{
		const int pivot_index = this->partition(low, high);

		// Recursively calls for the partitions
		this->quick_sort(low, pivot_index - 1);
		this->quick_sort(pivot_index + 1, high);
	}
}

viz::sort::QuickSort::QuickSort(SortSpace* sort_space, const float step_delay)
	: Sort(sort_space, step_delay), current_action_index_(0), is_base_sort_running_(false)
{
}

void viz::sort::QuickSort::run_sort_step()
{
	if (this->current_action_index_ < this->actions_.size())
	{
		this->actions_[this->current_action_index_]();
		this->current_action_index_++;
	}
	else
	{
		if (!this->is_base_sort_running_)
		{
			State::get_state_instance().sort.visualizer_mode = sort_visualizer_mode::completed;
		}
	}
}

void viz::sort::QuickSort::reset()
{
	Sort::reset();
	this->current_action_index_ = 0;
}

void viz::sort::QuickSort::start_sort()
{
	Sort::start_sort();
	this->current_action_index_ = 0;
	this->array_copy_ = this->sort_space_->box_heights;
	this->actions_.clear();
	this->is_base_sort_running_ = true;

	/*
	thread::ThreadPool::get_instance().queue_job([this]()
	{
		this->quick_sort(0, this->array_copy_.size() - 1);
		this->is_base_sort_running_ = false;
	});*/
	this->quick_sort(0, this->array_copy_.size() - 1);
	this->is_base_sort_running_ = false;
}

void viz::sort::MergeSort::merge(const int left, const int middle, const int right)
{
	int n1 = middle - left + 1;
	int n2 = right - middle;

	std::vector<int> left_array(n1), right_array(n2);

	for (int i = 0; i < n1; i++)
		left_array[i] = this->array_copy_[left + i];
	for (int j = 0; j < n2; j++)
		right_array[j] = this->array_copy_[middle + 1 + j];

	int i = 0, j = 0, k = left;

	while (i < n1 && j < n2)
	{
		if (left_array[i] <= right_array[j])
		{
			this->array_copy_[k] = left_array[i];
			auto val = left_array[i];
			this->actions_.emplace_back([this, k, val]()
			{
				this->sort_space_->box_heights[k] = val;
			});
			i++;
		}
		else
		{
			this->array_copy_[k] = right_array[j];
			auto val = right_array[j];
			this->actions_.emplace_back([this, k, val]()
			{
				this->sort_space_->box_heights[k] = val;
			});
			j++;
		}
		k++;
	}

	while (i < n1)
	{
		this->array_copy_[k] = left_array[i];
		auto val = left_array[i];
		this->actions_.emplace_back([this, k, val]()
		{
			this->sort_space_->box_heights[k] = val;
		});
		i++;
		k++;
	}

	while (j < n2)
	{
		this->array_copy_[k] = right_array[j];
		auto val = right_array[j];
		this->actions_.emplace_back([this, k, val]()
		{
			this->sort_space_->box_heights[k] = val;
		});
		j++;
		k++;
	}
}

void viz::sort::MergeSort::merge_sort(const int left, const int right)
{
	if (left < right)
	{
		int middle = left + (right - left) / 2;

		this->merge_sort(left, middle);
		this->merge_sort(middle + 1, right);

		this->merge(left, middle, right);
	}
}

viz::sort::MergeSort::MergeSort(SortSpace* sort_space, const float step_delay)
	: Sort(sort_space, step_delay), current_action_index_(0), is_base_sort_running_(false)
{
}

void viz::sort::MergeSort::run_sort_step()
{
	if (this->current_action_index_ < this->actions_.size())
	{
		this->actions_[this->current_action_index_]();
		this->current_action_index_++;
	}
	else
	{
		if (!this->is_base_sort_running_)
		{
			State::get_state_instance().sort.visualizer_mode = sort_visualizer_mode::completed;
		}
	}
}

void viz::sort::MergeSort::reset()
{
	Sort::reset();
	this->current_action_index_ = 0;
}

void viz::sort::MergeSort::start_sort()
{
	Sort::start_sort();
	this->current_action_index_ = 0;
	this->array_copy_ = this->sort_space_->box_heights;
	this->actions_.clear();
	this->is_base_sort_running_ = true;
	this->actions_.clear();

	/*
	thread::ThreadPool::get_instance().queue_job([this]()
	{
		this->merge_sort(0, this->array_copy_.size() - 1);
		this->is_base_sort_running_ = false;
	});*/
	this->merge_sort(0, this->array_copy_.size() - 1);
	this->is_base_sort_running_ = false;
}

int viz::sort::RadixSort::get_max() const
{
	int max = this->array_copy_[0];
	for (size_t i = 1; i < this->array_copy_.size(); i++)
	{
		if (this->array_copy_[i] > max)
		{
			max = this->array_copy_[i];
		}
	}
	return max;
}

void viz::sort::RadixSort::count_sort(int exp)
{
	int n = this->array_copy_.size();
	std::vector<int> output(n);
	std::vector<int> count(10, 0);

	for (int i = 0; i < n; i++)
	{
		count[(this->array_copy_[i] / exp) % 10]++;
	}

	for (int i = 1; i < 10; i++)
	{
		count[i] += count[i - 1];
	}

	for (int i = n - 1; i >= 0; i--)
	{
		output[count[(this->array_copy_[i] / exp) % 10] - 1] = this->array_copy_[i];
		count[(this->array_copy_[i] / exp) % 10]--;
	}

	for (int i = 0; i < n; i++)
	{
		this->array_copy_[i] = output[i];
		auto val = output[i];
		this->actions_.emplace_back([this, i, val]()
		{
			this->sort_space_->box_heights[i] = val;
		});
	}
}

viz::sort::RadixSort::RadixSort(SortSpace* sort_space, const float step_delay)
	: Sort(sort_space, step_delay), current_action_index_(0), is_base_sort_running_(false)
{
}

void viz::sort::RadixSort::run_sort_step()
{
	if (this->current_action_index_ < this->actions_.size())
	{
		this->actions_[this->current_action_index_]();
		this->current_action_index_++;
	}
	else
	{
		if (!this->is_base_sort_running_)
		{
			State::get_state_instance().sort.visualizer_mode = sort_visualizer_mode::completed;
		}
	}
}

void viz::sort::RadixSort::reset()
{
	Sort::reset();
	this->current_action_index_ = 0;
}

void viz::sort::RadixSort::start_sort()
{
	Sort::start_sort();
	this->current_action_index_ = 0;
	this->array_copy_ = this->sort_space_->box_heights;
	this->actions_.clear();
	this->is_base_sort_running_ = true;

	int max = get_max();

	for (int exp = 1; max / exp > 0; exp *= 10)
	{
		count_sort(exp);
	}

	this->is_base_sort_running_ = false;
}

bool viz::sort::BogoSort::is_sorted() const
{
	for (size_t i = 0; i < this->sort_space_->box_heights.size() - 1; i++)
	{
		if (this->sort_space_->box_heights[i] > this->sort_space_->box_heights[i + 1])
		{
			return false;
		}
	}

	return true;
}

viz::sort::BogoSort::BogoSort(SortSpace* sort_space, const float step_delay)
	: Sort(sort_space, step_delay * 20)
{
}

void viz::sort::BogoSort::run_sort_step()
{
	if (this->is_sorted())
	{
		State::get_state_instance().sort.visualizer_mode = sort_visualizer_mode::completed;
	}
	else
	{
		this->sort_space_->randomize();
	}
}

void viz::sort::BogoSort::reset()
{
	Sort::reset();
}

void viz::sort::BogoSort::start_sort()
{
	Sort::start_sort();
}
