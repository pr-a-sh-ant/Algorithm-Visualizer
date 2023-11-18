#include "Entity.h"

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

bool Entity::entity_over(const sf::Vector2i& pos2) const
{
	if (this->pos.x < pos2.x and this->pos.x + this->dim.x > pos2.x)
	{
		if (this->pos.y < pos2.y and this->pos.y + this->dim.y > pos2.y)
		{
			return true;
		}
		return false;
	}
	return false;
}
