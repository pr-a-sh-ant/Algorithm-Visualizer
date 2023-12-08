#include "Entity.h"
#include <iostream>

viz::Entity::Entity(const int x, const int y, const int width, const int height)
	: position(x, y), dimensions(width, height)
{
}

viz::Entity::Entity(const sf::Vector2i& position, const sf::Vector2i& dimensions)
	: position(position), dimensions(dimensions)
{
}

bool viz::Entity::is_mouse_over(const sf::Vector2i position) const
{
	return position.x >= this->position.x && position.x <= this->position.x + this->dimensions.x &&
		position.y >= this->position.y && position.y <= this->position.y + this->dimensions.y;
}