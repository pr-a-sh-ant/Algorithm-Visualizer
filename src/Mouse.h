#pragma once

#include <SFML/Graphics.hpp>
// class App;

class Mouse
{

	public:
		sf::Vector2i pos;
		bool clicked;
		void update(sf::RenderWindow& window);
};