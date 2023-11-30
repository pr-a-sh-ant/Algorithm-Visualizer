#pragma once

#include "App.h"
#include "Button.h"
#include <queue>
#include "sort_alg.h"
#include "array.h"

class App;

class Sort
{
public:
    Sort(App *app);
    ~Sort();
    App *app;
    AlgorithmSort algorithm;
    Array array;
    const std::vector<int> &current_state;

    sf::RectangleShape renderbox;
    sf::RectangleShape bar;

    int currentAlgorithm = 0;
    float barwidth;

    void init();
    void draw();
    void update();
};