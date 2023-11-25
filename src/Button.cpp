#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Mouse.h"
#include <iostream>
#include "State.h"
#include <iostream>

Button::Button(int x, int y, std::string text, int width, int height, std::string func) : Entity(x, y, width, height)
{
	this->name_button = text;
	this->rect.setPosition(x, y);
	this->rect.setSize(sf::Vector2f(width, height));

	if (!font.loadFromFile("src/public/font.ttf"))
	{
		std::cout << "Error loading font" << std::endl;
		return;
	}

	this->text = new sf::Text(text, this->font, 40);
	this->text->setPosition(x + 50, y + 10);

	this->func = func;

	this->pressed = false;
}

void Button::centerScale(int scale)
{
	rect.setSize(sf::Vector2f(dim.x + scale, dim.y + scale));
	rect.setPosition(pos.x - scale / 2, pos.y - scale / 2);
}

void Button::update(Mouse *mouse, state *appState)

{
	if (this->mouse_over(mouse->pos))
	{

		if (mouse->clicked)
		{
			this->hovered = false;
			this->pressed = true;
		}
		else
		{
			this->hovered = true;
			this->pressed = false;
		}
	}
	else
	{
		this->hovered = false;
		this->pressed = false;
	}

	if (this->name_button == "Exit" || this->name_button == "Back")
	{
		this->rect.setFillColor(sf::Color(208, 23, 28));
		if (this->hovered)
			this->rect.setFillColor(sf::Color(224, 15, 18));
	}

	else if (this->name_button == "Search")
	{
		this->rect.setFillColor(sf::Color(63, 182, 143));
		if (this->hovered)
			this->rect.setFillColor(sf::Color(123, 216, 143));
	}

	else
	{
		this->rect.setFillColor(sf::Color(9, 57, 120));
		if (this->hovered)
		{
			this->rect.setFillColor(sf::Color(19, 98, 168));
		}
	}
	if (this->pressed)
	{
		this->rect.setFillColor(sf::Color::Blue);
		std::cout << "SCREEN :" << appState->screen << std::endl;
		// std::cout<<"SCREEN :"<<this->func<<std::endl;
		mouse->clicked = false;

		stateChanger(appState);
	}
}

void Button::draw(sf::RenderWindow *window)
{

	window->draw(this->rect);
	// error while drawing text fsr
	window->draw(*this->text);
}

void Button::stateChanger(state *appState)
{

	if (this->func == "goSort")
	{
		appState->screen = 2;
	}
	else if (this->func == "goSearch")
	{
		appState->screen = 1;
	}
	else if (this->func == "goBack")
	{
		appState->screen = 0;
	}
	else if (this->func == "modeMaze")
	{
		appState->mode = 0;
	}
	else if (this->func == "modeDestination")
	{
		appState->mode = 1;
	}
	else if (this->func == "modeStart")
	{
		appState->mode = 2;
	}

	else if (this->func == "setSearching")
	{
		appState->startSearch = 1;
	}
}