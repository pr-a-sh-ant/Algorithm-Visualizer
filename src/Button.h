#pragma once

class App;
g
#include "App.h"
#include "Entity.h"
#include "Mouse.h"


class Button : public Entity
{
    public:
        Button(int x, int y, int width, int height);
       
        bool pressed;

        ~Button();
        void centerScale(int scale);
        void update(App *app);
    

};

