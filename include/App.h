#pragma once

#include <SFML/Graphics.hpp>
#include "SearchWindow.h"
#include "HomeWindow.h"

namespace viz
{
	class App
	{
	public:
		sf::RenderWindow* window;
		viz::window::Window* selected_window;
		viz::window::SearchWindow* search_window;
		viz::window::HomeWindow* home_window;
		float delta_time_seconds;
		sf::Clock clock;
		sf::Event sf_event;
		// TODO: Sort Window
		App();
		~App();

		void draw();
		void update();
		void handle_state(); // user inputs (mouse click, move etc.)

		// Runs the app
		void run();
	};
}

/*
#include "Mouse.h"
#include "Search.h"
#include <SFML/Graphics.hpp>
#include "Home.h"
#include "State.h"
#include "Sort.h"

class Search;
class Mouse;
class Home;
class Sort;

class App
{
public:
	App();
	Search *search;
	Mouse *mouse;
	Home *home;
	Sort *sort;

	float deltime;

	sf::RenderWindow *window;
	sf::Clock clock;
	sf::Event sfEvent;
	sf::Font font;

	state *appState;

	void init_window();
	void init_variables();
	void init_search();
	void init_home();
	void init_sort();

	void draw();

	void update();
	void updateSFMLevents();

	void run();
	~App();
};*/
