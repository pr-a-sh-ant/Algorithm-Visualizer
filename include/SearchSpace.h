#pragma once

#include "Maze.h"
#include <vector>

namespace viz::search
{
	class SearchSpace
	{
	private:
		sf::Vector2i dimensions_;
		viz::Maze* maze_; // Pointer to maze (not owned)
		std::vector<int> parents_;
		std::vector<bool> visited_;

	public:
		SearchSpace(viz::Maze* maze);

		// Getters
		[[nodiscard]]
		sf::Vector2i get_parent(const sf::Vector2i& box_index) const; // Returns the parent of a box
		[[nodiscard]]
		bool is_visited(const sf::Vector2i& box_index) const; // Returns the visited status of a box
		[[nodiscard]]
		sf::Vector2i get_dimensions() const; // Returns the dimensions of the maze
		[[nodiscard]]
		viz::Maze* get_maze() const; // Returns the maze
		[[nodiscard]]
		sf::Vector2i get_start_box() const; // Returns the start box
		[[nodiscard]]
		sf::Vector2i get_goal_box() const; // Returns the goal box

		// Setters
		void set_parent(const sf::Vector2i& parent_box_index, const sf::Vector2i& child_box_index); // Sets the parent of a box
		void set_as_visited(const sf::Vector2i& box_index); // Sets the visited status of a box
		void set_as_explored(const sf::Vector2i& box_index); // Sets the explored status of a box
		void set_as_path(const sf::Vector2i& box_index); // Sets the path status of a box

		[[nodiscard]]
		std::vector<sf::Vector2i> get_valid_actions(const sf::Vector2i& box_index) const; // Returns the valid actions of a box
		void reset(); // Resets the search space
	};
}