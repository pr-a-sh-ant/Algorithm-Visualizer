#pragma once

#include "Mouse.h"
#include "Search.h"
#include <SFML/Graphics.hpp>
#include "Home.h"

class Search;
class Mouse;
class Home;

class App
{
public:
	App();
	Mouse *mouse;
	Search *search;
	Home *home;

	float deltime;

	sf::RenderWindow *window;
	sf::Clock clock;
	sf::Event sfEvent;
	sf::Font font;

	int *current;
	void init_window();
	void init_variables();
	void init_search();
	void init_home();

	void draw();

	void update();
	void updateSFMLevents();

	void run();
	~App();
};
