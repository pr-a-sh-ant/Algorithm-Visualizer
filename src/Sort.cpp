#include "Sort.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "App.h"

Sort::Sort(App *app) : array(Array(100)), algorithm(array), current_state(algorithm.getCurrentState())
{
    this->app = app;
    init();

    renderbox.setSize(800, 600);
    renderbox.setPosition(0, 0);
}

void Sort::init()
{
}

void Sort::draw()
{
    barwidth = static_cast<float>(window.getSize().x) / currentState.size();
    for (size_t i = 0; i < currentState.size(); i++)
    {
        bar.setSize(sf::Vector2f(barWidth, currentState[i] * 5));
        bar.setPosition(i * barWidth, window.getSize().y - bar.getSize().y);
        bar.setFillColor(sf::Color::Black);
        this->app->window->draw(bar);
    }
}

void Sort::update()
{
    switch (currentAlgorithm)
    {
    case 0:
        algorithm.bubbleSort();
        break;
    case 1:
        algorithm.insertionSort();
        break;
    case 2:
        algorithm.mergeSort();
        break;
    case 3:
        algorithm.quickSort();
        break;
    }
}