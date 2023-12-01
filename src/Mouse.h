#pragma once

#include <SFML/Graphics.hpp>

class Mouse
{	
	public:
		Mouse();
		sf::Vector2i pos;
		bool clicked;
		void update(sf::RenderWindow &window);
};