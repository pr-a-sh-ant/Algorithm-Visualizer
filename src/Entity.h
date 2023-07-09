#pragma once
#include <SFML/Graphics.hpp>
#include "Mouse.h"

namespace viz
{
	class Mouse;

	class Entity
	{
	private:
		/* data */
	public:
		sf::Vector2i pos;
		sf::Vector2i dim;
		sf::RectangleShape rect;
		Entity(int x, int y, int width, int height);
		Entity(const sf::Vector2i& position, const sf::Vector2i& dimensions);

		Entity() = default;

		bool clicked=false;
		bool mouse_over=false;

		void update();

		bool collides_with(const Entity* entity2) const;
		bool collides_with(const Mouse* mouse) const;
		~Entity();
	};
}
