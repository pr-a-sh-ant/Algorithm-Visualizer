#include "Mouse.h"

#include <SFML/Graphics.hpp>

Mouse::Mouse(){
	this->clicked=false;
	this->pos = sf::Vector2i(0,0);
}

void Mouse::update(sf::RenderWindow &window)
{
	this->pos = sf::Mouse::getPosition(window);
}

