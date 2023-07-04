#include "App.h"
#include <SFML/Graphics.hpp>
#include "Mouse.h"
#include <iostream>

App::App()
{
    sf::VideoMode mode = sf::VideoMode::getDesktopMode();
	this->window = new sf::RenderWindow(mode, "SFML works!");
    this->window->setFramerateLimit(144);
    this->circle = new sf::CircleShape(100.f);
    this->circle->setFillColor(sf::Color::Green);
    std::cout<<"PPP"<<std::endl;
    this->mouse = new Mouse(this);
}

void App::update()
{
	while (this->window->isOpen())
    {
        this->mouse->update();
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

void App::render()
{
    
        this->window->clear();
    
        this->window->draw(*this->circle);

        this->mouse->render();

        this->window->display();
}
