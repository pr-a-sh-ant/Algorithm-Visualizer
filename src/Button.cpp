#include "Button.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "Mouse.h"

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
