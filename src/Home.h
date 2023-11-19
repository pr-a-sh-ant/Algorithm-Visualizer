#pragma once

#include "App.h"
#include <SFML/Graphics.hpp>
#include "Entity.h"

class Entity;
class App;

class Home
{

public:
    Home(App *app);
    ~Home();
    App *app;

    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Text searchAlgo;
    sf::Text sortAlgo;
    sf::Text exit;

    // Entity *entity;

    std::vector<Entity *> entities;

    void init();
    void init_buttons();

    void update();
    void draw();

};