#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Mouse.h"
#include <iostream>
#include "App.h"

Button::Button(int x, int y, int width=256, int height=64):Entity(x, y, width, height){

    this->rect.setPosition(x, y);
	this->rect.setSize(sf::Vector2f(width, height));
	this->rect.setOutlineThickness(2);
	this->rect.setOutlineColor(sf::Color::White);
	this->rect.setFillColor(sf::Color::Green);

	sf::Font font;

	if (!font.loadFromFile("src/public/font.ttf"))
	{
		std::cout << "Error loading font" << std::endl;
		return;
	}

	this->text = new sf::Text("Search Algo", font, 60);
	this->text->setPosition(x, y);

	this->pressed=false;

}


void Button::centerScale(int scale)
{
	rect.setSize(sf::Vector2f(dim.x + scale, dim.y + scale));
	rect.setPosition(pos.x - scale / 2, pos.y - scale / 2);
}

void Button::update(Mouse *mouse)
    
{
	if(this->mouse_over(mouse->pos)){
    
		if(mouse->clicked)
		{
			this->pressed=true;
			this->hovered = false;
		}
		else{
			this->hovered = true;
			this->pressed=false;
		}

	}
	else{
		this->hovered = false;
		this->pressed=false;
		
	}

	
		if(this->pressed){
			this->rect.setFillColor(sf::Color::Blue);
		}
		else if(this->hovered){
			this->rect.setFillColor(sf::Color::Red);
		}
		else{
			this->rect.setFillColor(sf::Color::Green);			
		}
}

void Button::draw(sf::RenderWindow *window){
	
	window->draw(this->rect);
	//error while drawing text fsr
	// window->draw(*this->text);
}