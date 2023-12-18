#pragma once

#include "Mouse.h"

namespace viz
{
	// Enumeration defining mouse click modes for search visualization
	enum class search_mouse_click_mode
	{
		none = 0,
		start,
		goal,
		wall,
		weight
	};

	// Enumeration defining visualizer modes for search visualization
	enum class search_visualizer_mode
	{
		none = 0,
		searching,
		backtracking,
		completed
	};

	// Enumeration defining visualizer modes for sorting visualization
	enum class sort_visualizer_mode
	{
		none = 0,
		sorting,
		completed
	};

	// Struct to maintain the state of the search visualization
	struct search_state
	{
		search_mouse_click_mode mouse_click_mode = search_mouse_click_mode::none;
		search_visualizer_mode visualizer_mode = search_visualizer_mode::none;
	};

	// Struct to maintain the state of the sorting visualization
	struct sort_state
	{
		sort_visualizer_mode visualizer_mode = sort_visualizer_mode::none;
	};

	class State
	{
	private:
		static State* state_instance_ptr_; // Singleton instance pointer
		State() = default; // Private default constructor

	public:
		search_state search; // State for the search visualization
		Mouse mouse; // State of mouse
		sort_state sort; // State for the sort visualization

		// Update the mouse position based on the input
		void update_mouse(const sf::Vector2i& mouse_position);

		// Check if the state class is initialized
		static bool is_initialized()
		{
			return state_instance_ptr_ != nullptr;
		}

		// Destroy the state instance
		static void destroy_state_instance()
		{
			if (state_instance_ptr_ != nullptr)
			{
				delete state_instance_ptr_;
				state_instance_ptr_ = nullptr;
			}
		}

		// Get the instance of the state
		static State& get_state_instance()
		{
			if (state_instance_ptr_ == nullptr)
			{
				state_instance_ptr_ = new State();
			}

			return *state_instance_ptr_;
		}
	};
}
