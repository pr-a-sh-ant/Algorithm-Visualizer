#include "Sort.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "App.h"

Sort::Sort(App *app) : array(Array(100)), algorithm(array), current_state(algorithm.getCurrentState())
{
    this->app = app;

    renderbox.setSize(sf::Vector2f(1000,1000));
    renderbox.setPosition(25, 25);
    
    // this->app->appState->sortAlg = 0;

    this->buttons.push_back(new Button(1150, 50, "Sort", 300, 80, "setSorting"));

    this->buttons.push_back(new Button(1200, 650, "Reset", 500, 80, "resetSort"));

    this->buttons.push_back(new Button(1200, 550, "Insertion", 500, 80, "insertMode"));

    this->buttons.push_back(new Button(1200, 450, "Bubble", 500, 80, "bubbleMode"));

    this->buttons.push_back(new Button(1200, 880, "Exit", 200, 80, "goBack"));


}



void Sort::init()
{   
        sorting=false;
        this->app->appState->startSort=false;
        algorithm.resetSorting();
        this->app->appState->clear=0;


}

void Sort::draw()
{
    barwidth = static_cast<float>(renderbox.getSize().x) / current_state.size();
    
    for (int i = 0; i < buttons.size(); i++)
    {

        buttons[i]->draw(this->app->window);
    }


    this->app->window->draw(renderbox);
    for (size_t i = 0; i < current_state.size(); i++)
    {   
    
        bar.setSize(sf::Vector2f(barwidth , current_state[i] * 5));
        bar.setPosition(25 + (i * barwidth) , renderbox.getSize().y - bar.getSize().y);
        bar.setFillColor(sf::Color::Black);

        this->app->window->draw(bar);
    }
}

void Sort::update()
{

    
    if(this->app->appState->startSort){
        sorting=true;
    }

    if(sorting){

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
    this->currentAlgorithm = this->app->appState->sortAlg;
     for (int i = 0; i < buttons.size(); i++)
    {
        buttons[i]->update(this->app->mouse, this->app->appState);
    }

    if(this->app->appState->clear){
        std::cout<<"CLEARING SORT";
        this->init();

    }

}