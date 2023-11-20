#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "App.h"

class App;



class Button : public Entity
{
    public:
        Button(int x, int y, int width, int height);
       
        bool pressed;

        ~Button();
        void centerScale(int scale);
        void update(App *app);
    

};

