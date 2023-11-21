#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Mouse.h"
#include <iostream>
#include "App.h"

Button::Button(int x, int y, std::string text, int width = 256, int height = 64) : Entity(x, y, width, height)
{
	this->name_button = text;
	this->rect.setPosition(x, y);
	this->rect.setSize(sf::Vector2f(width, height));

	if (!font.loadFromFile("src/public/font.ttf"))
	{
		std::cout << "Error loading font" << std::endl;
		return;
	}

	this->text = new sf::Text(text, this->font, 60);
	this->text->setPosition(x + 50, y + 10);
}

void Button::centerScale(int scale)
{
	rect.setSize(sf::Vector2f(dim.x + scale, dim.y + scale));
	rect.setPosition(pos.x - scale / 2, pos.y - scale / 2);
}

void Button::update(Mouse *mouse)

{
	if (this->mouse_over(mouse->pos))
	{

		if (mouse->clicked)
		{
			this->hovered = false;
		}
		else
		{
			this->hovered = true;
		}
	}
	else
	{
		this->hovered = false;
	}

	if (this->name_button == "Exit" || this->name_button == "Back" || this->name_button == "Clear")
	{
		this->rect.setFillColor(sf::Color(170, 19, 23));
	}
	else
	{
		this->rect.setFillColor(sf::Color(9, 57, 120));
	}

	if (this->hovered)
	{
		if (this->name_button == "Exit" || this->name_button == "Back")
		{
			this->rect.setFillColor(sf::Color(224, 15, 18));
		}
		else
		{
			this->rect.setFillColor(sf::Color(19, 98, 168));
		}
	}
}

void Button::draw(sf::RenderWindow *window)
{

	window->draw(this->rect);
	// error while drawing text fsr
	window->draw(*this->text);
}