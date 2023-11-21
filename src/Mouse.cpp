#include <SFML/Graphics.hpp>
#include "Mouse.h"
#include <iostream>


void Mouse::update(sf::RenderWindow& window)
{
	sf::Vector2i pos = sf::Mouse::getPosition(window);
	std::cout<<pos.x<<" "<<pos.y<<std::endl;

	
}

