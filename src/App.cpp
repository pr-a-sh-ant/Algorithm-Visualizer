#include <SFML/Graphics.hpp>
#include "Mouse.h"
#include "App.h"
#include <iostream>
#include "start_page.cpp"

viz::App::App()
{
	sf::VideoMode mode = sf::VideoMode::getDesktopMode();
	this->window = new sf::RenderWindow(mode, "SFML works!");
	this->window->setFramerateLimit(144);
	this->mouse = new Mouse(this);
	this->screen = new Screen(this);
	this->scene = new int(0);
}

void viz::App::renderStartPage()
{
	while (*scene != -1)
	{
		switch (*scene)
		{
		case 0:
			// Run Start Page
			runStartScreen(scene, this->window);
			break;

		default:
			return;
			// Run Search Algorithm

			// Run Sort Algorithm
		}
	}
}

// void viz::App::update()
// {
// 	while (this->window->isOpen())
// 	{
// 		this->mouse->update();
// 		this->screen->update();

// 		for (auto event = sf::Event{}; this->window->pollEvent(event);)
// 		{
// 			if (event.type == sf::Event::Closed)
// 			{
// 				this->window->close();
// 			}
// 		}
// 		this->render();
// 	}
// }

// void viz::App::render()
// {
// 	this->window->clear();

// 	this->mouse->render();
// 	this->screen->render();

// 	this->window->display();
// }
