#pragma once
#include "Entity.h"
#include "Mouse.h"
#include <SFML/Graphics.hpp>

class Button : public Entity
{
private:
    /* data */
public:
    Button(int x, int y, std::string, int width, int height);
    ~Button();

    bool pressed;
    bool hovered;
    sf::Text *text;

    sf::Font font;

    void centerScale(int scale);
    void update(Mouse *mouse);
    void draw(sf::RenderWindow *window);
};
