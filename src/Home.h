#pragma once
#include "App.h"
#include "Button.h"

class App;
class Button;

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


    std::vector<Button *> entities;

    void init();
    void init_buttons();

    void update();
    void draw();

};