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

namespace viz
{
	class Mouse
	{
	public:
		sf::Vector2f pos;
		sf::Vector2f prev_pos;
		bool is_left_button_down;

		Mouse()
		{
			this->is_left_button_down = false;
			pos = sf::Vector2f(0, 0);
			prev_pos = sf::Vector2f(0, 0);
		}
	};
}