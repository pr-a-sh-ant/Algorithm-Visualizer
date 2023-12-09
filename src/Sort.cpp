#include "Sort.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "App.h"

Sort::Sort(App *app) : array(Array(128)), algorithm(array), current_state(algorithm.getCurrentState())
{
    this->app = app;

    renderbox.setSize(sf::Vector2f(1000, 1000));
    renderbox.setPosition(25, 25);

    textAlgo = new sf::Text("Sort Alogrithms", this->app->font, 60);
    this->textAlgo->setPosition(1250, 200);
    // this->app->appState->sortAlg = 0;

    this->buttons.push_back(new Button(1150, 50, "Start Sort", 300, 80, "setSorting"));

    this->buttons.push_back(new Button(1550, 50, "Reset", 300, 80, "resetSort"));

    this->buttons.push_back(new Button(1350, 400, "Insertion", 300, 80, "insertMode"));

    this->buttons.push_back(new Button(1350, 300, "Bubble", 300, 80, "bubbleMode"));

    this->buttons.push_back(new Button(1200, 880, "Back", 200, 80, "goBack"));
}

void Sort::init()
{
    sorting = false;
    this->app->appState->startSort = false;
    algorithm.resetSorting();
    this->app->appState->clear = 0;
}

void Sort::draw()
{
    barwidth = static_cast<float>(renderbox.getSize().x) / current_state.size();

    this->app->window->draw(*this->textAlgo);

    for (int i = 0; i < buttons.size(); i++)
    {

        buttons[i]->draw(this->app->window);
    }

    this->app->window->draw(renderbox);
    for (size_t i = 0; i < current_state.size(); i++)
    {

        bar.setSize(sf::Vector2f(barwidth, current_state[i] * 5));
        bar.setPosition(25 + (i * barwidth), renderbox.getSize().y - bar.getSize().y);
        bar.setFillColor(sf::Color::Black);

        this->app->window->draw(bar);
    }
}

void Sort::update()
{

    totalTime += this->app->deltime;

    if (this->app->appState->startSort)
    {
        sorting = true;
    }

    if (!this->app->appState->clearSort)
    {
        this->init();
        this->app->appState->clearSort = 1;
    }
    if (sorting )
    {
        sf::sleep(sf::milliseconds(5));
        switch (currentAlgorithm)
        {
        case 0:
            algorithm.merge();

            break;
        case 1:
            algorithm.merge();

            break;
        case 2:
            algorithm.bogo();
            break;
        }
    }
    this->currentAlgorithm = this->app->appState->sortAlg;
    for (int i = 0; i < buttons.size(); i++)
    {
        buttons[i]->update(this->app->mouse, this->app->appState);
    }

    if (this->app->appState->clear)
    {
        this->init();
    }
}