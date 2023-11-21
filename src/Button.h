#pragma once 

#include "Entity.h"
#include "App.h"

class App;

class Button : public Entity
{
private:
    /* data */
public:
    Button(int x, int y, int width, int height);
    ~Button();

    bool pressed;

    void centerScale(int scale);
    void update(App *app);
};

