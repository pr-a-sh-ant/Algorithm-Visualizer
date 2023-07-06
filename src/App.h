#pragma once
#include <SFML/Graphics.hpp>
#include "Mouse.h"
#include "Entity.h"
#include "Screen.h"

class Mouse;
class Screen;


class App
{
private:
    /* data */
public:
    
    sf::RenderWindow *window;
    Mouse *mouse;
    Screen *screen;
    
    App();
    void update();
    void render();
    
    

};