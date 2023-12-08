#pragma once

#include <SFML/Graphics.hpp>

namespace viz
{
	class Entity
	{
	private:

	public:
		Entity(const int x, const int y, const int width, const int height);
		Entity(const sf::Vector2i& position, const sf::Vector2i& dimensions);
		Entity() = default;

		sf::Vector2i position;
		sf::Vector2i dimensions;
		sf::RectangleShape rectangle;

		bool is_mouse_over(const sf::Vector2i position) const;
	};
}
