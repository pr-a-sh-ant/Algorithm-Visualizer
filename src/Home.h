#pragma once

#include "App.h"
#include <SFML/Graphics.hpp>

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

    void
    init();

    void update();
    void draw();
};