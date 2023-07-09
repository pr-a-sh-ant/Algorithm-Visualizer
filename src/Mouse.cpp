#include <SFML/Graphics.hpp>
class App;
#include "App.h"

#include "Mouse.h"
#include <iostream>


viz::Mouse::Mouse(App* app)
{
	this->app = app;

	this->font.loadFromFile("src/font.ttf");
	this->PosText.setFont(this->font);
	this->PosText.setCharacterSize(60);
	this->PosText.setFillColor(sf::Color::Red);
	this->PosText.setOrigin(this->PosText.getLocalBounds().width / 2., this->PosText.getLocalBounds().height / 2.);


	this->rectangle = new sf::CircleShape;
	this->rectangle->setRadius(10);
	this->rectangle->setFillColor(sf::Color::Red);
}

void viz::Mouse::update()
{
	this->pos = sf::Vector2i(sf::Mouse::getPosition(*app->window).x, sf::Mouse::getPosition(*app->window).y);


	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->clicked=true;
	}
	else{
		this->clicked=false;
	}
}

void viz::Mouse::render()
{
	this->PosText.setString(std::to_string(this->pos.x) + " " + std::to_string(this->pos.y));

	this->rectangle->setPosition(this->pos.x - this->rectangle->getRadius() / 2,
	                             this->pos.y - this->rectangle->getRadius() / 2);

	this->app->window->draw(*this->rectangle);
	this->app->window->draw(this->PosText);
}
