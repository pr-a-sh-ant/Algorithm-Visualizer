#pragma once

#include <SFML/Graphics.hpp>


class Entity
{
private:

public:
	Entity(const int x, const int y, const int width, const int height);
	Entity(const sf::Vector2i& position, const sf::Vector2i& dimensions);
	Entity() = default;

	sf::Vector2i pos;
	sf::RectangleShape rect;
	sf::Vector2i dim;

	bool mouse_over(sf::Vector2i pos2);
};
