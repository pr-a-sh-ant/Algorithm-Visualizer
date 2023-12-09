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
