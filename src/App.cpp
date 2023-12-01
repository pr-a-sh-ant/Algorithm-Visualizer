#include "App.h"
#include "Search.h"
#include <iostream>
#include "Home.h"
#include "State.h"

App::App()
{
	init_window();
	// std::cout << "window inited............." << std::endl;
	init_variables();
	// std::cout << "APP INIT DONE......" << std::endl;
}

void App::init_window()
{
	sf::VideoMode mode = sf::VideoMode::getDesktopMode();
	this->window = new sf::RenderWindow(mode, "SFML works!", sf::Style::Fullscreen);
	this->mouse = new Mouse();
	init_search();
	init_home();
	init_sort();

}

void App::init_variables()
{
	this->appState = new state;
	this->appState->screen = 0;
	this->appState->startSearch = 0;
	this->appState->resetScreen = 1;
	this->appState->mode = 3;
	// std::cout << "numeric variables inited............." << std::endl;
	deltime = 0.0f;
	if (!font.loadFromFile("src/public/font.ttf"))
	{
		std::cout << "Error loading font" << std::endl;
		return;
	}

}

void App::init_search()
{
	this->search = new Search(this);
}

void App::init_home()
{

	this->home = new Home(this);
}

void App::init_sort()
{	
	this->sort = new Sort(this);
	
}

void App::draw()
{
	// std::cout << "drawing............." << std::endl;
		
	this->window->clear();
	if (appState->screen == 0)
	{	
		// std::cout << "drawing home............." << std::endl;
		this->home->draw();
	}
	else if (appState->screen == 1)
	{
		this->search->draw();
	}
	else if (appState->screen == 2)
	{
		this->sort->draw();
	}
	else if (appState->screen == 1)
	{	
		
		this->search->draw();
	}
	this->window->display();
}

void App::update()
{	
	// std::cout << "updating............." << std::endl;
	updateSFMLevents();
	if (appState->screen == 0)
	{
		// std::cout << "updating Home............." << std::endl;
		this->home->update();
		if(this->appState->resetScreen){
			this->search->reset();
			this->sort->init();
			this->appState->resetScreen=0;
		}
	}
	else if (appState->screen == 1)
	{
		this->search->update();
	}
	else if (appState->screen == 2)
	{	
		// std::cout << "updating sort............." << std::endl;
		this->sort->update();
	}
	else if (appState->screen == -1)
	{
		this->window->clear();
		this->window->close();
	}

	

	mouse->update(*this->window);
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
				this->appState->screen = 1;
			}
		}
		else if (sfEvent.type == sf::Event::MouseButtonPressed)
		{
			this->mouse->clicked = true;
		}
		else if (sfEvent.type == sf::Event::MouseButtonReleased)
		{
			this->mouse->clicked = false;
		}
	}
}

void App::run()
{
	while (this->window->isOpen())
	{	
		// std::cout << "running............." << std::endl;
		this->update();

		this->draw();
	}
}

App::~App()
{
	delete this->mouse;
}