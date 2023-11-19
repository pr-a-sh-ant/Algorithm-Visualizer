#include "App.h"
#include "Search.h"
#include <iostream>
#include "Home.h"
#include "Mouse.h"

App::App()
{
	init_window();
	init_variables();
	std::cout << "APP INIT DONE......" << std::endl;
}

void App::init_window()
{
	sf::VideoMode mode = sf::VideoMode::getDesktopMode();
	this->window = new sf::RenderWindow(mode, "SFML works!", sf::Style::Fullscreen);
	this->mouse = new Mouse;
	init_screens();
	
}

void App::init_variables()
{
	deltime = 0.0f;
	current = new int(0);
	if (!font.loadFromFile("src/public/font.ttf"))
	{
		std::cout << "Error loading font" << std::endl;
		return;
	}
}

void App::init_screens()
{
	this->search = new Search(this);
	this->home = new Home(this);
}


void App::draw()
{
	this->window->clear();
	if (*current == 0)
	{
		this->home->draw();
	}
	else if (*current == 1)
	{
		this->search->draw();
	}
	this->window->display();
}

void App::update()
{
	updateSFMLevents();
	std::cout<<this->mouse->pos.x;
	this->mouse->update(*this->window);
	if (*current == 0)
	{
		this->home->update();
	}
	else if (*current == 1)
	{
		this->search->update();
	}
	else if (*current == -1)
	{
		this->window->clear();
		this->window->close();
	}
	}

void App::updateSFMLevents()
{
	deltime = clock.restart().asSeconds();
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
			this->window->close();
		if (sfEvent.type == sf::Event::KeyPressed)
		{
			if (sfEvent.key.code == sf::Keyboard::Q || sfEvent.key.code == sf::Keyboard::Escape)
			{
				this->window->close();
			}
			else if (sfEvent.key.code == sf::Keyboard::S)
			{
				this->search->searching= true;
			}
		}
	}
}

void App::run()
{
	while (this->window->isOpen())
	{

		this->update();

		this->draw();
	}
}

App::~App()
{
	delete this->mouse;
}