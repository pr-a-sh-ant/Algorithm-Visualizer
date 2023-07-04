#include <SFML/Graphics.hpp>
class App;
#include "App.h"

#include "Mouse.h"
#include <iostream>


Mouse::Mouse(App* app)
{
	this->app = app;
	
	// this->font->loadFromFile("Roboto-Regular.ttf");
	// this->PosText->setFont(*this->font);
	// this->PosText->setCharacterSize(60);
	// this->PosText->setFillColor(sf::Color::Black);
	// this->PosText->setOrigin(this->PosText->getLocalBounds().width / 2., this->PosText->getLocalBounds().height / 2.);

	this->rectangle = new sf::CircleShape(10.f);
    this->rectangle->setFillColor(sf::Color::Red);
}

void Mouse::update()
{
	this->pos = sf::Vector2i(sf::Mouse::getPosition(*app->window).x,sf::Mouse::getPosition(*app->window).y);
	 

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		std::cout << sf::Mouse::getPosition(*app->window).y << std::endl;
		
	}
}

void Mouse::render()
{
	// this->PosText->setString(std::to_string(this->pos->x));
	// this->PosText->setString(std::to_string(this->pos->y));

	// this->rectangle->setPosition(this->pos->x, this->pos->y);

	this->app->window->draw(*this->rectangle);
}
