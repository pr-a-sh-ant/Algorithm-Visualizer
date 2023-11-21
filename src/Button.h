#pragma once
#include "Entity.h"
#include "Mouse.h"
#include <SFML/Graphics.hpp>
#include "State.h"

class Button : public Entity
{
private:
    /* data */
public:
    Button(int x, int y, std::string, int width, int height);
    ~Button();

    std::string name_button;
    bool hovered;
    sf::Text *text;

    sf::Font font;

    void centerScale(int scale);
    void update(Mouse *mouse,state* appState);
    void draw(sf::RenderWindow *window);
};
