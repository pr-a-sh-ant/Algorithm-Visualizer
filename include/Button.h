#pragma once
#include <functional>

#include "Mouse.h"
#include <SFML/Graphics.hpp>
#include <string>

namespace viz
{
    class Button
    {
    private:
        /* data */
    public:
        Button(const sf::Vector2f &position, const sf::Vector2f &dimensions, std::string text, const std::string &font, const sf::Color fill_color, const sf::Color fill_color_hover, const std::function<void()> &callback);
        ~Button();

        sf::RectangleShape rectangle;
        sf::Text *text;
        std::string button_name;

        sf::Color fill_color;
        sf::Color fill_color_hover;

        bool pressed;
        bool hovered;

        // callback function
        std::function<void()> callback;

        sf::Font font;

        // Returns true if the mouse is over the button
        bool is_mouse_over(const sf::Vector2f &mouse_position) const;
        // Handle the mouse state
        void handle_mouse(const viz::Mouse &mouse);
        // Draw the button
        void draw(sf::RenderWindow &window) const;
        // Updates the button
        void update();
    };
}
