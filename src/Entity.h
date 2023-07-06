#pragma once
#include <SFML/Graphics.hpp>
#include "Mouse.h"

class Mouse;

class Entity
{
private:
    /* data */
public:
    sf::Vector2i pos;
	sf::Vector2i dim;
    sf::RectangleShape rect;
    Entity(const int x, const int y, const int width, const int height);
	Entity(const sf::Vector2i& position, const sf::Vector2i& dimensions);
	
    Entity() = default;
    
    bool operator==(const Entity *entity2) const;
    bool operator==(const Mouse *mouse) const;
    ~Entity();
};

