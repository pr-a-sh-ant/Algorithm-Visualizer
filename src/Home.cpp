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

    searchAlgo.setString("Search \nAlgorithm");
    searchAlgo.setFont(app->font);
    searchAlgo.setCharacterSize(60);
    searchAlgo.setPosition(sf::Vector2f(350, 530));

    sortAlgo.setString("Sort \nAlgorithm");
    sortAlgo.setFont(app->font);
    sortAlgo.setCharacterSize(60);
    sortAlgo.setPosition(sf::Vector2f(1300, 530));

    exit.setString("Exit");
    exit.setFont(app->font);
    exit.setCharacterSize(60);
    exit.setPosition(sf::Vector2f(900, 880));
    exit.setFillColor(sf::Color::Black);
}

void Home::draw()
{
    app->window->draw(background);
    app->window->draw(sortAlgo);
    app->window->draw(searchAlgo);
    app->window->draw(exit);
}

void Home::update()
{
    searchAlgo.setFillColor(sf::Color(0xF6, 0xF1, 0xF1));
    exit.setFillColor(sf::Color(0, 0, 0));
    sortAlgo.setFillColor(sf::Color(0xF6, 0xF1, 0xF1));

    if (searchAlgo.getGlobalBounds().contains(sf::Mouse::getPosition(*(app->window)).x, sf::Mouse::getPosition(*(app->window)).y))
    {
        if (app->sfEvent.type == sf::Event::MouseButtonPressed)
        {
            *(app->current) = 1;
        }
        searchAlgo.setFillColor(sf::Color(0xAF, 0xD3, 0xE2));
    }
    if (sortAlgo.getGlobalBounds().contains(sf::Mouse::getPosition(*(app->window)).x, sf::Mouse::getPosition(*(app->window)).y))
    {
        if (app->sfEvent.type == sf::Event::MouseButtonPressed)
        {
            *(app->current) = 2;
        }
        sortAlgo.setFillColor(sf::Color(0xAF, 0xD3, 0xE2));
    }
    if (exit.getGlobalBounds().contains(sf::Mouse::getPosition(*(app->window)).x, sf::Mouse::getPosition(*(app->window)).y))
    {
        if (app->sfEvent.type == sf::Event::MouseButtonPressed)
        {
            *(app->current) = -1;
        }
        exit.setFillColor(sf::Color(0xAF, 0xD3, 0xE2));
    }
}
