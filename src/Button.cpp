#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Mouse.h"
#include <iostream>
#include "State.h"
#include <iostream>
/*
Button::Button(int x, int y, std::string text, int width, int height, std::string func) : Entity(x, y, width, height)
{
	this->name_button = text;
	this->rect.setPosition(x, y);
	this->rect.setSize(sf::Vector2f(width, height));

	if (!font.loadFromFile("Public/font.ttf"))
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

	else if (this->name_button == "Search" || this->name_button == "Start Sort")
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
		appState->resetScreen = 1;
	}
	else if (this->func == "goSearch")
	{
		appState->screen = 1;
		appState->resetScreen = 1;
	}
	else if (this->func == "goBack")
	{
		appState->screen = 0;
		appState->resetScreen = 1;
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
	else if (this->func == "setClear")
	{
		appState->clear = 1;
	}
	else if (this->func == "resetSort")
	{
		appState->clear = 1;
	}
	else if (this->func == "setSorting")
	{
		appState->startSort = 1;
	}
	else if (this->func == "insertMode")
	{
		appState->sortAlg = 1;
		appState->clearSort = 0;
	}
	else if (this->func == "bubbleMode")
	{
		appState->sortAlg = 0;
		appState->clearSort = 0;
	}
	else if(this->func == "exit"){
		appState->screen = -1;
	}
}
*/
viz::Button::Button(const sf::Vector2f& position, const sf::Vector2f& dimensions, std::string text, const std::string& font, const sf::Color fill_color, const sf::Color fill_color_hover, const std::function<void()>& callback)
	: button_name(std::move(text)), fill_color(fill_color), fill_color_hover(fill_color_hover), pressed(false), hovered(false), callback(callback)
{
	this->rectangle.setPosition(position);
	this->rectangle.setSize(dimensions);
	this->rectangle.setFillColor(fill_color);

	if (!this->font.loadFromFile(font))
	{
		throw std::runtime_error("Failed to load font");
	}

	this->text = new sf::Text(button_name, this->font, 40);
	this->text->setPosition(position.x + 50, position.y + 10);
}

viz::Button::~Button()
{
	delete this->text;
}

bool viz::Button::is_mouse_over(const sf::Vector2f& mouse_position) const
{
	return this->rectangle.getGlobalBounds().contains(mouse_position);
}

void viz::Button::handle_mouse(const viz::Mouse& mouse)
{
	this->hovered = this->is_mouse_over(mouse.pos);
	this->pressed = this->hovered && mouse.is_left_button_pressed;
}

void viz::Button::draw(sf::RenderWindow& window) const
{
	window.draw(this->rectangle);
	window.draw(*this->text);
}

void viz::Button::update()
{
	if (this->pressed && this->callback)
	{
		this->callback();
	}
	this->rectangle.setFillColor(this->hovered ? this->fill_color_hover : this->fill_color);
}
