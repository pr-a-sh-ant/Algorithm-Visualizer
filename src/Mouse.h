#pragma once
class App;

#include <SFML/Graphics.hpp>
#include "App.h"
class Mouse
{
private:
	sf::Font *font;
	sf::Text *PosText;


public:
	Mouse(App *app);
	App *app;
	sf::Vector2i *pos;
	void init();
	void update();
	void render();

};

