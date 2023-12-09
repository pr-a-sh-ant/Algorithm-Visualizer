#pragma once

#include "Mouse.h"

/*
struct state
	{
		int screen = 0;
		int mode = 0;
		int startSearch = 0;
		int startSort = 0;
		int clear = 0;
		int sortAlg = 0;
		int resetScreen = 0;
		int clearSort = 0;
	} ;
*/

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

	struct search_state
	{
		search_mouse_click_mode mouse_click_mode = search_mouse_click_mode::none;
		search_visualizer_mode visualizer_mode = search_visualizer_mode::none;
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
		viz::Mouse mouse; // State of mouse

		void update_mouse(const sf::Vector2i& mouse_position);

		// Returns the instance of the state
		inline static State& get_state_instance()
		{
			if (State::state_instance_ptr_ == nullptr)
			{
				State::state_instance_ptr_ = new State();
			}

			return *State::state_instance_ptr_;
		}
	};

}

	