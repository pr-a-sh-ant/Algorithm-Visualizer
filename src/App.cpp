#include <SFML/Graphics.hpp>
#include "Mouse.h"
#include "App.h"
#include <iostream>

viz::App::App()
{
	sf::VideoMode mode = sf::VideoMode::getDesktopMode();
	this->window = new sf::RenderWindow(mode, "SFML works!");
	this->window->setFramerateLimit(144);
	this->mouse = new Mouse(this);
	this->screen = new Screen(this);
}

void viz::App::update()
{
	while (this->window->isOpen())
	{
		this->mouse->update();
		this->screen->update();

		for (auto event = sf::Event{}; this->window->pollEvent(event);)
		{
			if (event.type == sf::Event::Closed)
			{
				this->window->close();
			}
		}
		this->render();
	}
}


void viz::App::render()
{
	this->window->clear();

	this->mouse->render();
	this->screen->render();

	this->window->display();
}
