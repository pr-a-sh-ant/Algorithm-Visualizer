#pragma once
#include "App.h"
#include "Button.h"

class App;
class Button;

class Home
{

public:
    Home(App *app);
    
    App *app;

    sf::Texture backgroundTexture;
    sf::RectangleShape background;

    std::vector<Button *> entities;

    void init();
    void init_buttons();

    void update();
    void draw();
};