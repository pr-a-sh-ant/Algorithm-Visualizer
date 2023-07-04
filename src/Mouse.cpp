#include <SFML/Graphics.hpp>
class App;
#include "App.h"

#include "Mouse.h"
#include <iostream>


Mouse::Mouse(App* app)
{
	this->app = app;
	if (!this->font->loadFromFile("/Fonts/Roborto-Regular.ttf"))
	{
		return;
		// throw "Font Not Found";
	}

	this->PosText->setFont(*this->font);
	this->PosText->setCharacterSize(60);
	this->PosText->setFillColor(sf::Color::Black);
	this->PosText->setOrigin(this->PosText->getLocalBounds().width / 2., this->PosText->getLocalBounds().height / 2.);
}

void Mouse::update()
{
	this->pos->x = sf::Mouse::getPosition(*app->window).x;
	this->pos->y = sf::Mouse::getPosition(*app->window).y;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		std::cout << "CLicked" << std::endl;
	}
	this->render();
}

void Mouse::render()
{
	this->PosText->setString(std::to_string(this->pos->x));
	this->PosText->setString(std::to_string(this->pos->y));

	this->app->window->draw(*this->PosText);
}
