#include "Entity.h"
#include "Mouse.h"


Entity::Entity(const int x, const int y, const int width, const int height)
{
	this->pos = sf::Vector2i(x, y);
	this->dim = sf::Vector2i(width, height);
}

Entity::Entity(const sf::Vector2i& position, const sf::Vector2i& dimensions)
{
	this->pos = position;
	this->dim = dimensions;
}

bool Entity::mouse_over(Mouse *mouse)
{
	if (this->pos.x < mouse->pos.x && this->pos.x + this->dim.x > mouse->pos.x)
	{
		if (this->pos.y < mouse->pos.y && this->pos.y + this->dim.y > mouse->pos.y)
		{
			return true;
		}
		return false;
	}
	return false;
}
