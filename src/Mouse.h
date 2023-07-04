#pragma once
class App;

#include <SFML/Graphics.hpp>
#include "App.h"

class Mouse
{
private:
	sf::Font* font;
	sf::Text* PosText;

public:
	App* app;
	sf::Vector2i* pos;

	Mouse(App* app);
	void update();
	void render();
};
