#pragma once
#include <SFML/Graphics.hpp>
#include "Mouse.h"
#include "Entity.h"
#include "Screen.h"


namespace viz
{
	class Mouse;
	class Screen;

	class App
	{
	private:
		/* data */
	public:
		sf::RenderWindow* window;
		viz::Mouse* mouse;
		viz::Screen* screen;

		App();
		void update();
		void render();
	};
}
