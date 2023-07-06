#include "Entity.h"
#include "Mouse.h"

viz::Entity::Entity(const int x, const int y, const int width, const int height)
{
	this->pos = sf::Vector2i(x, y);
	this->dim = sf::Vector2i(width, height);
    this->rect.setPosition(x, y);
	this->rect.setSize(sf::Vector2f(width, height));
	this->rect.setOutlineThickness(2);
	this->rect.setOutlineColor(sf::Color::White);
	this->rect.setFillColor(sf::Color::Green);
}

viz::Entity::Entity(const sf::Vector2i& position, const sf::Vector2i& dimensions)
{
	this->pos = position;
	this->dim = dimensions;
}

bool viz::Entity::collides_with(const Entity* entity2) const
{
	if (this->pos.x < entity2->pos.x and this->pos.x + this->dim.x > entity2->pos.x)
	{
		if (this->pos.y < entity2->pos.y and this->pos.y + this->dim.y > entity2->pos.y)
		{
			return true;
		}
		return false;
	}
	return false;
}

bool viz::Entity::collides_with(const Mouse* mouse) const
{
	if (this->pos.x < mouse->pos.x and this->pos.x + this->dim.x > mouse->pos.x)
	{
		if (this->pos.y < mouse->pos.y and this->pos.y + this->dim.y > mouse->pos.y)
		{
			return true;
		}
		return false;
	}
	return false;
}
