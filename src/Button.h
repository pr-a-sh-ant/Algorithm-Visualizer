#pragma once
#include "Entity.h"
#include "Mouse.h"


class Button : public Entity
{
private:
    /* data */
public:
    Button(int x, int y, int width, int height);
    ~Button();

    bool pressed;
    bool hovered;

    void centerScale(int scale);
    void update(Mouse *mouse);
};

