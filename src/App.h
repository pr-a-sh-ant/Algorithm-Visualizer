#pragma once
#include <SFML/Graphics.hpp>
#include "Mouse.h"
class App
{
private:
    /* data */
public:
    
    sf::RenderWindow *window;
    sf::CircleShape *circle;
    Mouse *mouse;

    App();
    void update();
    void render();

};