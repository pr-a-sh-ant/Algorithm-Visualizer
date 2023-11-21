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

    init_buttons();
}

void Home::init_buttons()
{

    this->entities.push_back(new Button(1300, 530,256,64));
    
    
    this->entities.push_back(new Button(900, 880,256,64));
    
    this->entities.push_back(new Button(350, 530,256,64));


}


void Home::draw()
{
    app->window->draw(background);
    app->window->draw(sortAlgo);
    app->window->draw(searchAlgo);
    app->window->draw(exit);
    for(int i=0; i < entities.size(); i++){
        std::cout<<std::endl<<"entity"<<entities[i]->pos.x<<std::endl;
        app->window->draw(entities[i]->rect);
            
    }    
}

void Home::update()
{
  
}