#pragma once

#include <SFML/Graphics.hpp>
#include "App.h"

namespace viz
{
	class App;

	class Mouse
	{
	private:
		sf::Font font;
		sf::Text PosText;

	public:
		App* app;
		sf::Vector2i pos;
		sf::CircleShape* rectangle;

		bool clicked=false;


		Mouse(App* app);
		void update();
		void render();
	};
}
