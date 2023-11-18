#pragma once


#include "Mouse.h"
#include "Search.h"
#include <SFML/Graphics.hpp>

class Search;
class Mouse;

class App
{
    public:
        App();
        sf::RenderWindow* window;
        Mouse* mouse;
        Search* search;
        
        float deltime;	
        sf::Clock clock;
        sf::Event sfEvent;

        void init_window() ;
        void init_variables();
        void init_search();

        void draw();
        
        void update();
        void updateSFMLevents();

        void run();
        ~App();
};
