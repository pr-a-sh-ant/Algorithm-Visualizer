#include "Button.h"
#include "Mouse.h"
#include <iostream>

Button::Button(int x, int y, int width=256, int height=64):Entity(x, y, width, height){

    this->rect.setPosition(x, y);
	this->rect.setSize(sf::Vector2f(width, height));
	this->rect.setOutlineThickness(2);
	this->rect.setOutlineColor(sf::Color::White);
	this->rect.setFillColor(sf::Color::Green);

}


void Button::centerScale(int scale)
{
	rect.setSize(sf::Vector2f(dim.x + scale, dim.y + scale));
	rect.setPosition(pos.x - scale / 2, pos.y - scale / 2);
}

void Button::update(App *app)
{
	if(this->mouse_over(app->mouse)){

		if(app->mouse->clicked)
		{
 		
			this->pressed=true;
		}
		else{
			this->pressed=false;
		}


	}

	std::cout<<this->pressed<<std::endl;
}