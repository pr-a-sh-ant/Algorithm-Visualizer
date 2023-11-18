#pragma once
class Search;

#include "Mouse.h"
#include "Search.h"
#include <SFML/Graphics.hpp>



class App
{
private:
    /* data */
public:
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
};
