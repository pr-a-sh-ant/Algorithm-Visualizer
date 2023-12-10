#include <SFML/Graphics.hpp>
#include "Mouse.h"
#include <iostream>


Mouse::Mouse(){
	this->clicked=false;
	this->pos = sf::Vector2i(0,0);
}

void Mouse::update(sf::RenderWindow &window)
{
	this->pos = sf::Mouse::getPosition(window);
}

