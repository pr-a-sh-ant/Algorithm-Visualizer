#include "Search.h"

#include <SFML/Graphics.hpp>

#include "State.h"
#include "App.h"

viz::search::Search::Search(SearchSpace* search_space, const float step_delay)
	: search_space_(search_space), step_delay_(step_delay), step_clock_(0.0f), searching_(false), back_tracking_(false),
	  back_track_box_(sf::Vector2i(-1, -1))
{
}


void viz::search::Search::start_search()
{
	this->searching_ = true;
	this->back_track_box_ = sf::Vector2i(-1, -1);
	this->back_tracking_ = false;
}

void viz::search::Search::run_back_track_step()
{
	if (this->back_track_box_ == sf::Vector2i(-1, -1))
	{
		this->back_track_box_ = this->search_space_->get_goal_box();
	}
	try
	{
		this->back_track_box_ = this->search_space_->get_parent(this->back_track_box_);
	}
	catch (const std::runtime_error&)
	{
		this->back_tracking_ = false;
		return;
	}
	if (this->back_track_box_ == this->search_space_->get_start_box())
	{
		this->back_tracking_ = false;
		return;
	}

	this->search_space_->set_as_path(this->back_track_box_);
}

void viz::search::Search::set_step_delay(const float step_delay)
{
	this->step_delay_ = step_delay;
}

float viz::search::Search::get_step_delay() const
{
	return this->step_delay_;
}

void viz::search::Search::reset()
{
	this->step_clock_ = 0.0f;
	this->search_space_->reset();
	this->searching_ = false;
	this->back_tracking_ = false;
	this->back_track_box_ = sf::Vector2i(-1, -1);
}

void viz::search::Search::update(const float& delta_time_seconds)
{
	auto& global_state = State::get_state_instance();
	global_state.search.visualizer_mode = this->back_tracking_
		                                      ? search_visualizer_mode::backtracking
		                                      : this->searching_
		                                      ? search_visualizer_mode::searching
		                                      : search_visualizer_mode::none;

	this->step_clock_ += delta_time_seconds;
	if (this->step_clock_ < this->step_delay_)
	{
		return;
	}
	step_clock_ -= this->step_delay_;

	if (this->back_tracking_)
	{
		this->run_back_track_step();
	}
	else if (this->searching_)
	{
		try
		{
			this->run_search_step();
		}
		catch (const viz::search::destination_not_found_exception&)
		{
			this->searching_ = false;
			this->back_tracking_ = false;

			// TODO: Handle not found
		}
	}
}

bool viz::search::Search::is_searching() const
{
	return this->searching_;
}

viz::search::BreadthFirstSearch::BreadthFirstSearch(SearchSpace* search_space, const float step_delay)
	: Search(search_space, step_delay)
{
	this->queue_ = std::queue<sf::Vector2i>();
}

void viz::search::BreadthFirstSearch::run_search_step()
{
	// If the search is running but the queue is empty, raise exception
	if (this->queue_.empty())
	{
		throw viz::search::destination_not_found_exception();
	}

	const auto current_box_index = this->queue_.front(); // Get the current box index
	this->queue_.pop(); // Pop the current box index from the queue

	// if the current box is the goal box, stop the search
	if (current_box_index == this->search_space_->get_goal_box())
	{
		this->searching_ = false;
		this->back_tracking_ = true;
		return;
	}

	// Push the valid actions of the current box to the queue
	for (const auto& action : this->search_space_->get_valid_actions(current_box_index))
	{
		this->queue_.push(action);
		this->search_space_->set_parent(current_box_index, action);
		this->search_space_->set_as_visited(action);
	}

	if (current_box_index == this->search_space_->get_start_box())
	{
		return;
	}
	this->search_space_->set_as_explored(current_box_index); // Set the current box as explored
}

void viz::search::BreadthFirstSearch::start_search()
{
	if (State::get_state_instance().search.visualizer_mode != search_visualizer_mode::none)
	{
		return;
	}
	Search::start_search();

	this->queue_ = std::queue<sf::Vector2i>(); // Reset the queue

	// Sets the start box as visited and adds it to the queue
	this->search_space_->set_as_visited(this->search_space_->get_start_box());
	this->queue_.push(this->search_space_->get_start_box());
}

viz::search::DepthFirstSearch::DepthFirstSearch(SearchSpace* search_space, const float step_delay)
	: Search(search_space, step_delay)
{
	this->stack_ = std::stack<sf::Vector2i>();
}

void viz::search::DepthFirstSearch::run_search_step()
{
	// If the search is running but the stack is empty, raise exception
	if (this->stack_.empty())
	{
		throw viz::search::destination_not_found_exception();
	}

	const auto current_box_index = this->stack_.top(); // Get the current box index
	this->stack_.pop(); // Pop the current box index from the queue

	// if the current box is the goal box, stop the search
	if (current_box_index == this->search_space_->get_goal_box())
	{
		this->searching_ = false;
		this->back_tracking_ = true;
		return;
	}

	// Push the valid actions of the current box to the queue
	for (const auto& action : this->search_space_->get_valid_actions(current_box_index))
	{
		this->stack_.push(action);
		this->search_space_->set_parent(current_box_index, action);
		this->search_space_->set_as_visited(action);
	}

	if (current_box_index == this->search_space_->get_start_box())
	{
		return;
	}
	this->search_space_->set_as_explored(current_box_index); // Set the current box as explored
}

void viz::search::DepthFirstSearch::start_search()
{
	if (State::get_state_instance().search.visualizer_mode != search_visualizer_mode::none)
	{
		return;
	}
	Search::start_search();

	this->stack_ = std::stack<sf::Vector2i>(); // Reset the stack

	// Sets the start box as visited and adds it to the stack
	this->search_space_->set_as_visited(this->search_space_->get_start_box());
	this->stack_.push(this->search_space_->get_start_box());
}

viz::search::BestFirstSearch::BestFirstSearch(SearchSpace* search_space, const float step_delay)
	: Search(search_space, step_delay)
{
	this->priority_queue_ = std::priority_queue<sf::Vector2i, std::vector<sf::Vector2i>, std::function<bool(
		                                            const sf::Vector2i&, const sf::Vector2i&)>>(
		[this](const sf::Vector2i& lhs, const sf::Vector2i& rhs)
		{
			const auto goal_box = this->search_space_->get_goal_box();
			return abs(goal_box.x - lhs.x) + abs(goal_box.y - lhs.y) > abs(goal_box.x - rhs.x) +
				abs(goal_box.y - rhs.y);
		});
}

void viz::search::BestFirstSearch::run_search_step()
{
	// If the search is running but the priority queue is empty, raise exception
	if (this->priority_queue_.empty())
	{
		throw viz::search::destination_not_found_exception();
	}

	const auto current_box_index = this->priority_queue_.top(); // Get the current box index
	this->priority_queue_.pop(); // Pop the current box index from the queue

	// if the current box is the goal box, stop the search
	if (current_box_index == this->search_space_->get_goal_box())
	{
		this->searching_ = false;
		this->back_tracking_ = true;
		return;
	}

	// Push the valid actions of the current box to the queue
	for (const auto& action : this->search_space_->get_valid_actions(current_box_index))
	{
		this->priority_queue_.push(action);
		this->search_space_->set_parent(current_box_index, action);
		this->search_space_->set_as_visited(action);
	}

	if (current_box_index == this->search_space_->get_start_box())
	{
		return;
	}
	this->search_space_->set_as_explored(current_box_index); // Set the current box as explored
}

void viz::search::BestFirstSearch::start_search()
{
	if (State::get_state_instance().search.visualizer_mode != search_visualizer_mode::none)
	{
		return;
	}
	Search::start_search();

	this->priority_queue_ = std::priority_queue<sf::Vector2i, std::vector<sf::Vector2i>, std::function<bool(
		                                            const sf::Vector2i&, const sf::Vector2i&)>>(
		[this](const sf::Vector2i& lhs, const sf::Vector2i& rhs)
		{
			const auto goal_box = this->search_space_->get_goal_box();
			return abs(goal_box.x - lhs.x) + abs(goal_box.y - lhs.y) > abs(goal_box.x - rhs.x) +
				abs(goal_box.y - rhs.y);
		}); // Reset the priority queue

	// Sets the start box as visited and adds it to the stack
	this->search_space_->set_as_visited(this->search_space_->get_start_box());
	this->priority_queue_.push(this->search_space_->get_start_box());
}
