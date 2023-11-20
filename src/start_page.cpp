#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace sf;

inline void runStartScreen(int *scene, sf::RenderWindow *window)
{
    // Loading fonts
    sf::Font font;
    if (!font.loadFromFile("src/public/font.ttf"))
    {
        cout << "Error loading font" << endl;
        *scene = -1;
        return;
    }
    // Loading Background
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("src/public/start.jpg"))
    {
        cout << "Error loading Texture" << endl;
        *scene = -1;
        return;
    }

    // Seeting shapes and texts
    sf::Color transparentColor(225, 255, 225, 0);

    sf::RectangleShape background(sf::Vector2f(1920, 1080));

    sf::Text searchAlgo("Search Algo", font, 60);
    searchAlgo.setPosition(190, 760);

    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                *scene = -1;
                window->close();
            }

            if (event.type == Event::MouseButtonPressed)
            {
                cout << Mouse::getPosition(*window).x << " " << Mouse::getPosition(*window).y;
            }
        }

        window->clear(Color::Black);
        window->draw(background);

        window->draw(searchAlgo);

        window->display();
    }
}