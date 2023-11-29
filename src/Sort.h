#pragma once

#include "App.h"
#include "Button.h"
#include <queue>
#include "sort_alg.h"
#include "array.h"

using namespace sf;

class Algorithm;
class Array;
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

    RectangleShape renderbox;
    RectangleShape bar;

    int currentAlgorithm = 0;
    float barwidth;

    void init();
    void draw();
    void update();
};