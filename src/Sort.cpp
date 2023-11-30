#include "Sort.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "App.h"

Sort::Sort(App *app)
{
    this->app = app;
    this->array = new Array(100);
    this->algorithm = new AlgorithmSort(*array);
    this->current_state = algorithm->getCurrentState();

    renderbox.setSize(sf::Vector2f(1000, 1000));
    renderbox.setPosition(25, 25);
}

void Sort::init()
{
}

void Sort::draw()
{
    barwidth = static_cast<float>(renderbox.getSize().x) / current_state.size();

    this->app->window->draw(renderbox);
    for (size_t i = 0; i < current_state.size(); i++)
    {

        bar.setSize(sf::Vector2f(barwidth, current_state[i] * 5));
        bar.setPosition(25 + (i * barwidth), renderbox.getSize().y - bar.getSize().y);
        bar.setFillColor(sf::Color::Black);

        this->app->window->draw(bar);
    }
}

void Sort::reset()
{
    delete array;
    delete algorithm;

    this->array = new Array(100);
    this->algorithm = new AlgorithmSort(*array);

    this->current_state = algorithm->getCurrentState();
}

void Sort::update()
{
    switch (currentAlgorithm)
    {
    case 0:
        algorithm->bubbleSort();
        break;
    case 1:
        algorithm->insertionSort();
        break;
    case 2:
        algorithm->mergeSort();
        break;
    case 3:
        algorithm->quickSort();
        break;
    }
}