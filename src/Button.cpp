#include "Button.h"

Button::Button(int x, int y, int width=64, int height=256):Entity(x, y, width, height){

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