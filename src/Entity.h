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
	sf::Vector2i dim;

	bool entity_over(const sf::Vector2i& pos2) const;

	bool operator==(const Entity& other) const = default;
};
