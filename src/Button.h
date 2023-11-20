#include "Entity.h"


class Button : public Entity
{
private:
    /* data */
public:
    Button(int x, int y, int width, int height);
    sf::RectangleShape rect;
    ~Button();
    void centerScale(int scale);

};

