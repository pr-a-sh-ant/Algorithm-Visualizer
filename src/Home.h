#pragma once
#include "App.h"

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


    std::vector<Entity *> entities;

    void init();
    void init_buttons();

    void update();
    void draw();

};