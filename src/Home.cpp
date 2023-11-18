#include "Home.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "App.h"

Home::Home(App *app)
{
    this->app = app;
    init();
}

void Home::init()
{
    if (!backgroundTexture.loadFromFile("src/Public/start.jpg"))
    {
        std::cout << "Error loading Texture" << std::endl;
        return;
    }
    background.setSize((sf::Vector2f(1920, 1080)));
    background.setTexture(&backgroundTexture);
    background.setPosition(sf::Vector2f(0, 0));
}

void Home::draw()
{
    app->window->draw(background);
}