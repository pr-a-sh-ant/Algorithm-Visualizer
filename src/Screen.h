#pragma once
class App;


#include "App.h"
#include "Entity.h"

class Entity;

class Screen
{
private:
    /* data */
public:
    Screen(App *app);
    App *app;
    Entity *ent;
    std::vector<std::vector<Entity*>> box;
    ~Screen();
    void update();
    void init_box();
    void render();
};
