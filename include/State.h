#pragma once

#include "Mouse.h"

namespace viz
{
	enum class search_mouse_click_mode
	{
		none = 0,
		start,
		goal,
		wall,
		weight
	};

	enum class search_visualizer_mode
	{
		none = 0,
		searching,
		backtracking,
		completed
	};

	enum class sort_visualizer_mode
	{
		none = 0,
		sorting,
		completed
	};

	struct search_state
	{
		search_mouse_click_mode mouse_click_mode = search_mouse_click_mode::none;
		search_visualizer_mode visualizer_mode = search_visualizer_mode::none;
	};

	struct sort_state
	{
		sort_visualizer_mode visualizer_mode = sort_visualizer_mode::none;
	};

	class State;

	// Singleton class for storing the state of the application
	class State
	{
	private:
		static State* state_instance_ptr_;
		// constructor
		State() = default;

	public:
		search_state search; // State for the search visualization
		Mouse mouse; // State of mouse
		sort_state sort; // State for the sort visualization

		void update_mouse(const sf::Vector2i& mouse_position);

		// Returns true if the class is initialized
		static bool is_initialized()
		{
			return state_instance_ptr_ != nullptr;
		}

		// Destroys the state instance
		static void destroy_state_instance()
		{
			if (state_instance_ptr_ != nullptr)
			{
				delete state_instance_ptr_;
				state_instance_ptr_ = nullptr;
			}
		}

		// Returns the instance of the state
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
