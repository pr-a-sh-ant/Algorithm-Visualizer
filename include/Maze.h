#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "MazeBox.h"
#include "State.h"

namespace viz
{
	// Maze for the search visualization (singleton)
	class Maze
	{
	private:
		sf::Vector2f box_dimensions_; // Dimensions of the box
		std::vector<MazeBox*> boxes_; // Boxes in the maze
		sf::Vector2i start_box_; // Position of the start box
		sf::Vector2i goal_box_; // Position of the goal box
		sf::Vector2i boxes_in_maze_; // Dimensions of the maze(number of boxes)

		sf::Vector2f maze_start_position_; // Position of the maze on the screen
		sf::Vector2f maze_dimensions_; // Dimensions of the maze on the screen

		[[nodiscard]]
		inline sf::Vector2i get_hovered_box(const sf::Vector2f& mouse_position) const; // Get the box that the mouse is hovering over

	public:
		// Constructor (initializes the maze)
		Maze(const sf::Vector2f& box_dimensions, const sf::Vector2i& boxes_in_maze,
		     const sf::Vector2f& maze_start_position);

		// Destructor (deletes all the boxes)
		~Maze();

		Maze() = delete; // Delete default constructor
		Maze(const Maze&) = delete; // Delete copy constructor

		inline MazeBox& operator[](sf::Vector2i position); // Overload [] operator to access boxes in the maze
		inline MazeBox& operator()(int x, int y); // Overload () operator to access boxes in the maze
		[[nodiscard]]
		inline const MazeBox& at(sf::Vector2i position) const; // Get box at position
		void update_animation(const float& delta_time_seconds); // Update the animation of the boxes
		void draw_maze(sf::RenderWindow& window) const; // Draws the maze on the render window

		void set_box_type(const sf::Vector2i& position, const MazeBoxType type, const bool animate = true); // Set the type of the box at position
		void handle_event(const sf::Event& event); // Handle events (user input)
		void handle_state_change(const viz::State& state); // Handle state changes (mouse input)

		[[nodiscard]]
		sf::Vector2i get_start_box() const; // Get the start box
		[[nodiscard]]
		sf::Vector2i get_goal_box() const; // Get the goal box
		[[nodiscard]]
		sf::Vector2i get_boxes_in_maze() const; // Get the dimensions of the maze (number of boxes)

		void set_goal_box(const sf::Vector2i& position); // Set the goal box
		void set_start_box(const sf::Vector2i& position); // Set the start box
		void set_wall(const sf::Vector2i& position, const bool revert = false); // Set the wall at position (changes back to normal if revert is true and the box is already a wall)
		void reset(); // Reset the maze removing all the walls and searched boxes
		void clear(); // Clear the maze removing all the searched boxes but keeping the walls
	};


#pragma region Inline functions
	inline MazeBox& Maze::operator[](const sf::Vector2i position)
	{
		return *this->boxes_[position.x * this->boxes_in_maze_.x + position.y];
	}

	inline MazeBox& Maze::operator()(const int x, const int y)
	{
		return *this->boxes_[x * this->boxes_in_maze_.x + y];
	}

	[[nodiscard]]
	inline const MazeBox& Maze::at(const sf::Vector2i position) const
	{
		return *this->boxes_.at(position.x * this->boxes_in_maze_.x + position.y);
	}

	[[nodiscard]]
	inline sf::Vector2i Maze::get_hovered_box(const sf::Vector2f& mouse_position) const
	{
		// If the mouse is outside the maze, raise exception
		if (mouse_position.x < this->maze_start_position_.x ||
			mouse_position.y < this->maze_start_position_.y ||
			mouse_position.x > this->maze_start_position_.x + this->maze_dimensions_.x ||
			mouse_position.y > this->maze_start_position_.y + this->maze_dimensions_.y)
		{
			throw std::out_of_range("Mouse is out of maze");
		}

		// Get the box position
		const auto box_position = sf::Vector2i(
			static_cast<int>((mouse_position.x - this->maze_start_position_.x) / this->box_dimensions_.x),
			static_cast<int>((mouse_position.y - this->maze_start_position_.y) / this->box_dimensions_.y));

		// If the box position is out of range, raise exception
		if (box_position.x < 0 || box_position.y < 0 ||
			box_position.x >= this->boxes_in_maze_.x || box_position.y >= this->boxes_in_maze_.y)
		{
			throw std::out_of_range("Mouse is out of maze");
		}

		return box_position;
	}

#pragma endregion
}
