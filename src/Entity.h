#pragma once

#include <SFML/Graphics.hpp>
#include "Mouse.h"
#include "App.h"

class Mouse;
class App;

class Entity
{
private:

public:
	Entity(const int x, const int y, const int width, const int height);
	Entity(const sf::Vector2i& position, const sf::Vector2i& dimensions);
	Entity() = default;

	sf::Vector2i pos;
	sf::Vector2i dim;
	sf::RectangleShape rect;

	virtual void update(App *app)=0;

	bool mouse_over(Mouse *mouse);

};
