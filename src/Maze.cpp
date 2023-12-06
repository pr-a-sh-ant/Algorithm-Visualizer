#include "Maze.h"
#include <SFML/Graphics.hpp>
#include "MazeBox.h"
#include "State.h"

viz::Maze::Maze(const sf::Vector2f& box_dimensions, const sf::Vector2i& boxes_in_maze,
                const sf::Vector2f& maze_start_position)
	: box_dimensions_(box_dimensions), boxes_in_maze_(boxes_in_maze), maze_start_position_(maze_start_position)
{
	// Creates a sample rectangle to be used for all the boxes
	sf::RectangleShape sample_rectangle(box_dimensions_);
	sample_rectangle.setOutlineThickness(2);
	sample_rectangle.setOutlineColor(sf::Color::White);
	sample_rectangle.setFillColor(MazeBox::get_box_color(MazeBoxType::empty));

	// Resize the boxes vector and fill it with the sample rectangle
	this->boxes_.resize(
		static_cast<std::vector<MazeBox, std::allocator<MazeBox>>::size_type>(boxes_in_maze.x) * boxes_in_maze.y,
		MazeBox(sample_rectangle));

	// Sets the position of the boxes
	for (int x = 0; x < boxes_in_maze.x; x++)
	{
		for (int y = 0; y < boxes_in_maze.y; y++)
		{
			this->operator()(x, y).set_position(
				sf::Vector2f(maze_start_position.x + x * box_dimensions_.x,
				             maze_start_position.y + y * box_dimensions_.y));
		}
	}

	// Sets the dimensions of the maze
	this->maze_dimensions_ = sf::Vector2f(box_dimensions_.x * boxes_in_maze_.x, box_dimensions_.y * boxes_in_maze_.y);
	// Sets the start and goal box
	this->start_box_ = sf::Vector2i(boxes_in_maze_.x / 3, boxes_in_maze_.y / 3);
	this->start_box_ = sf::Vector2i(boxes_in_maze_.x - 1, boxes_in_maze_.y - 1);

	// Sets the type of the start and goal box
	this->operator[](this->start_box_).set_type(MazeBoxType::start, false);
	this->operator[](this->goal_box_).set_type(MazeBoxType::goal, false);
}

void viz::Maze::update_animation(const float& delta_time_seconds)
{
	for (auto& box : this->boxes_)
	{
		box.update_animation(delta_time_seconds);
	}
}

void viz::Maze::draw_maze(sf::RenderWindow& window) const
{
	// Draw the boxes that are not animating
	for (const auto& box : this->boxes_)
	{
		if (!box.is_animating())
		{
			window.draw(*box.get_drawable());
		}
	}

	// Draw the boxes that are animating
	for (const auto& box : this->boxes_)
	{
		if (box.is_animating())
		{
			window.draw(*box.get_drawable());
		}
	}
}

void viz::Maze::set_box_type(const sf::Vector2i& position, const MazeBoxType type, const bool animate)
{
	// If the position is out of range, raise exception
	if (position.x < 0 || position.y < 0 ||
		position.x >= this->boxes_in_maze_.x || position.y >= this->boxes_in_maze_.y)
	{
		throw std::out_of_range("Position is out of range");
	}

	this->operator[](position).set_type(type, animate);
}

void viz::Maze::handle_event(const sf::Event& event)
{
	const auto& state = State::get_state_instance();

	// If event is not a left mouse click, return
	if (state.search.visualizer_mode != search_visualizer_mode::none || event.type != sf::Event::MouseButtonPressed ||
		event.mouseButton.button != sf::Mouse::Left)
	{
		return;
	}

	sf::Vector2i current_box_position;
	try
	{
		current_box_position = this->get_hovered_box(state.mouse.pos);
	}
	catch (const std::out_of_range&)
	{
		return;
	}

	switch (state.search.mouse_click_mode)
	{
	case (search_mouse_click_mode::goal):
		set_goal_box(current_box_position);
		break;
	case (search_mouse_click_mode::start):
		set_start_box(current_box_position);
		break;
	case (search_mouse_click_mode::wall):
		set_wall(current_box_position, true);
		break;
	default:
		break;
	}
}

void viz::Maze::set_goal_box(const sf::Vector2i& position)
{
	// if clicking in non-empty box, return
	if (this->operator[](position).get_type() != MazeBoxType::empty)
	{
		return;
	}

	this->operator[](this->goal_box_).set_type(MazeBoxType::empty, true);
	this->goal_box_ = position;
	this->operator[](this->goal_box_).set_type(MazeBoxType::goal, true);
}

void viz::Maze::set_start_box(const sf::Vector2i& position)
{
	// if clicking in non-empty box, return
	if (this->operator[](position).get_type() != MazeBoxType::empty)
	{
		return;
	}

	this->operator[](this->start_box_).set_type(MazeBoxType::empty, true);
	this->start_box_ = position;
	this->operator[](this->start_box_).set_type(MazeBoxType::start, true);
}

void viz::Maze::set_wall(const sf::Vector2i& position, const bool revert)
{
	// if clicking in start or goal, return
	if (position == this->start_box_ || position == this->goal_box_)
	{
		return;
	}

	auto& box = this->operator[](position);
	box.set_type((revert && box.get_type() == MazeBoxType::obstacle) ? MazeBoxType::empty : MazeBoxType::obstacle,
	             true);
}

void viz::Maze::reset()
{
	for (auto& box : this->boxes_)
	{
		box.set_type(MazeBoxType::empty, false);
	}

	this->operator[](this->start_box_).set_type(MazeBoxType::start, false);
	this->operator[](this->goal_box_).set_type(MazeBoxType::goal, false);

	auto& state = viz::State::get_state_instance();
	state.search.visualizer_mode = viz::search_visualizer_mode::none;
	state.search.mouse_click_mode = viz::search_mouse_click_mode::none;
}
