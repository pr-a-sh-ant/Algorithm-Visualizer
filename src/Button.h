#include "App.h"
#include "Mouse.h"
#include "Entity.h"


class Button : public Entity
{
private:
    /* data */
public:
    Button(int x, int y, int width, int height);
    sf::RectangleShape rect;
    bool pressed;
    std::vector<Entity *> entities;

    ~Button();
    void centerScale(int scale);
    void update(App *app) override;
    

};

