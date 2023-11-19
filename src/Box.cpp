#include <SFML/Graphics.hpp>
#include "Box.h"
#include "Mouse.h"
#include <iostream>
#include "App.h"

Box::Box(int x, int y, int width = 32, int height = 32) : Entity(x, y, width, height)
{
	this->rect.setPosition(x, y);
	this->rect.setSize(sf::Vector2f(width, height));
	// std::cout<<this->rect.getPosition().x<<" ";
	// std::cout<<this->rect.getPosition().y<<std::endl;
	this->rect.setOutlineThickness(2);
	this->rect.setOutlineColor(sf::Color::White);
	this->rect.setFillColor(sf::Color::Green);
}

void Box::animate(float deltime)
{
	if (!animating)
	{
		return;
	}
	totalTime += deltime;
	// std::cout<<pos.x/32<<"Animating"<<pos.y/32<<std::endl;
	// std::cout<<totalTime<<" "<<switchTIme<<std::endl;

	if (totalTime >= switchTIme)
	{
		// std::cout<<totalTime<<"Animating"<<switchTIme<<std::endl;

		// TODO Better Implementation Upcomming
		// Nub fucker

		if (currentAnimation == 9)
		{
			currentAnimation = 0;
			animating = false;
		}

		rect.setFillColor(animColours[currentAnimation]);
		centerScale(scale[currentAnimation]);

		currentAnimation++;
		totalTime = 0;
	}
}

void Box::update(App *app){

	if(this->mouse_over(app->mouse) && app->mouse->clicked)
	{
		this->animating=true;


	}
	if (this->animating)
			{
				this->animate(app->deltime);
			}

}

void Box::is_path()
{
	this->currentAnimation = 0;
	this->animating = false;
	this->rect.setFillColor(sf::Color::Black);
	this->centerScale(scale[0]);
}

void Box::centerScale(int scale)
{
	rect.setSize(sf::Vector2f(dim.x + scale, dim.y + scale));
	rect.setPosition(pos.x - scale / 2, pos.y - scale / 2);
}
