#pragma once

#include <SFML/Graphics.hpp>

#include "SearchWindow.h"
#include "HomeWindow.h"
#include "SortWindow.h"

namespace viz
{
	class App
	{
	public:
		sf::RenderWindow* window;
		viz::window::Window* selected_window;
		viz::window::SearchWindow* search_window;
		viz::window::HomeWindow* home_window;
		viz::window::SortWindow* sort_window;

		float delta_time_seconds;
		sf::Clock clock;
		sf::Event sf_event;
		App();
		~App();

		void draw();
		void update();
		void handle_state(); // user inputs (mouse click, move etc.)

		// Runs the app
		void run();
	};
}