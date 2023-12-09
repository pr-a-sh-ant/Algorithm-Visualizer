#include "SearchSpace.h"

viz::search::SearchSpace::SearchSpace(Maze *maze)
	: dimensions_(maze->get_boxes_in_maze()), maze_(maze)
{
	this->parents_.resize(this->dimensions_.x * this->dimensions_.y, -1);
	this->visited_.resize(this->dimensions_.x * this->dimensions_.y, false);
}

sf::Vector2i viz::search::SearchSpace::get_parent(const sf::Vector2i &box_index) const
{
	if (this->parents_[box_index.y * this->dimensions_.x + box_index.x] == -1)
	{
		throw std::runtime_error("Parent of box is not set");
	}

	return {
		this->parents_[box_index.y * this->dimensions_.x + box_index.x] % this->dimensions_.x,
		this->parents_[box_index.y * this->dimensions_.x + box_index.x] / this->dimensions_.x};
}

bool viz::search::SearchSpace::is_visited(const sf::Vector2i &box_index) const
{
	return this->visited_[box_index.y * this->dimensions_.x + box_index.x];
}

sf::Vector2i viz::search::SearchSpace::get_dimensions() const
{
	return this->dimensions_;
}

viz::Maze *viz::search::SearchSpace::get_maze() const
{
	return this->maze_;
}

sf::Vector2i viz::search::SearchSpace::get_start_box() const
{
	return this->maze_->get_start_box();
}

sf::Vector2i viz::search::SearchSpace::get_goal_box() const
{
	return this->maze_->get_goal_box();
}

void viz::search::SearchSpace::set_parent(const sf::Vector2i &parent_box_index, const sf::Vector2i &child_box_index)
{
	this->parents_[child_box_index.y * this->dimensions_.x + child_box_index.x] =
		parent_box_index.y * this->dimensions_.x + parent_box_index.x;
}

void viz::search::SearchSpace::set_as_visited(const sf::Vector2i &box_index)
{
	this->visited_[box_index.y * this->dimensions_.x + box_index.x] = true;
}

void viz::search::SearchSpace::set_as_explored(const sf::Vector2i &box_index)
{
	this->maze_->operator[](box_index).set_type(MazeBoxType::searched, true);
}

void viz::search::SearchSpace::set_as_path(const sf::Vector2i &box_index)
{
	this->maze_->operator[](box_index).set_type(MazeBoxType::path, true);
}

std::vector<sf::Vector2i> viz::search::SearchSpace::get_valid_actions(const sf::Vector2i &box_index) const
{
	std::vector<sf::Vector2i> valid_actions;

	// If box to left, right, top and bottom exists, and are either empty or the goal, add them to the valid actions
	for (const auto &relative_position : std::vector<sf::Vector2i>{{-1, 0}, {0, 1}, {0, -1}, {1, 0}})
	{
		const auto absolute_position = box_index + relative_position;
		// Check if box is within bounds
		if (absolute_position.x < 0 || absolute_position.y < 0 ||
			absolute_position.x >= this->dimensions_.x || absolute_position.y >= this->dimensions_.y)
		{
			continue;
		}
		// Check if box is either empty or the goal
		if (this->maze_->at(absolute_position).get_type() != MazeBoxType::empty &&
			this->maze_->at(absolute_position).get_type() != MazeBoxType::goal)
		{
			continue;
		}
		// Check if the box is already visited
		if (this->is_visited(absolute_position))
		{
			continue;
		}

		// Add the box to the valid actions
		valid_actions.push_back(absolute_position);
	}

	return valid_actions;
}

void viz::search::SearchSpace::reset()
{
	for (auto &parent : this->parents_)
	{
		parent = -1;
	}

	for (size_t i = 0; i < this->visited_.size(); i++)
	{
		this->visited_[i] = false;
	}

	// TODO: Might need to reset maze weights
}
