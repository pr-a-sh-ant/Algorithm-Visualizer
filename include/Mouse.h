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
		bool is_left_button_pressed;

		Mouse()
			: pos(0, 0), prev_pos(0, 0), is_left_button_down(false), is_left_button_pressed(false)
		{
		}
	};
}