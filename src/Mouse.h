#pragma once

#include <SFML/Graphics.hpp>
// class App;

class Mouse
{	

	public:
		Mouse();
		sf::Vector2i pos;
		bool clicked;
		void update(sf::RenderWindow &window);
};