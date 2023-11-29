#include <SFML/Graphics.hpp>
#include "array.h"
#include "sort_alg.h"

inline int chorpp()
{
    // Create a window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Algorithm Visualizer");

    Array array(100);
    Algorithm algorithm(array);

    int currentAlgorithm = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

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

        window.clear(sf::Color::White);

        const auto &currentState = algorithm.getCurrentState();
        float barWidth = static_cast<float>(window.getSize().x) / currentState.size();

        for (size_t i = 0; i < currentState.size(); i++)
        {
            sf::RectangleShape bar(sf::Vector2f(barWidth, currentState[i] * 5));
            bar.setPosition(i * barWidth, window.getSize().y - bar.getSize().y);
            bar.setFillColor(sf::Color::Black);
            window.draw(bar);
        }

        window.display();

        sf::sleep(sf::milliseconds(5));

        if (algorithm.isSortingComplete())
        {
            currentAlgorithm++;
            if (currentAlgorithm > 3)
            {
                currentAlgorithm = 0;
            }
            algorithm.resetSorting();
        }
    }

    return 0;
}