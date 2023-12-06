#include <SFML/Graphics.hpp>
#include "Box.h"

Box::Box(int x, int y, const sf::RectangleShape& sample_rect, int width, int height,int type)
	: Entity(x, y, width, height), animatable_rectangle_(sample_rect)
{
	this->rect.setPosition(x, y);
	this->rect.setSize(sf::Vector2f(width, height));
	// std::cout<<this->rect.getPosition().x<<" ";
	// std::cout<<this->rect.getPosition().y<<std::endl;
	this->rect.setOutlineThickness(2);
	this->rect.setOutlineColor(sf::Color::White);
	this->rect.setFillColor(sf::Color::Green);
	this->type=type;
	// PP code
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
		if(this->type == 3){

			rect.setFillColor(animColours2[currentAnimation]);
		}
		else{

			rect.setFillColor(animColours[currentAnimation]);
		}
		centerScale(scale[currentAnimation]);

		currentAnimation++;
		totalTime = 0;
	}
}

void Box::is_path()
{
	this->currentAnimation = 0;
	this->animating = false;
	this->rect.setFillColor(sf::Color::Black);
	this->centerScale(scale[0]);
}

const sf::Drawable* Box::get_drawable()
{
	return this->animatable_rectangle_.get_drawable();
}

void Box::centerScale(int scale)
{
	rect.setSize(sf::Vector2f(dim.x + scale, dim.y + scale));
	rect.setPosition(pos.x - scale / 2, pos.y - scale / 2);
}

