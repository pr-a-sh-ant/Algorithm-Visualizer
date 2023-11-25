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

    init_buttons();
}

void Home::init_buttons()
{

    this->entities.push_back(new Button(1200, 650, "Sort Algorithm", 500, 80, "goSort"));

    this->entities.push_back(new Button(850, 880, "Exit", 200, 80, "goBack"));

    this->entities.push_back(new Button(250, 650, "Search Algorithm", 500, 80, "goSearch"));
}

void Home::draw()
{
    app->window->draw(background);
    for (int i = 0; i < entities.size(); i++)
    {

        entities[i]->draw(this->app->window);
    }
}

void Home::update()
{
    for (int i = 0; i < entities.size(); i++)
    {
        entities[i]->update(this->app->mouse, this->app->appState);
    }
}