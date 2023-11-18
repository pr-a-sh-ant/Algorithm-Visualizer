#pragma once
#include <SFML/Graphics.hpp>
#include "Box.h"

class Node
{
private:
	/* data */
public:
	Node(sf::Vector2i state, Node* parent, sf::Vector2i action, Box* box);
	Node(sf::Vector2i state, Box* box);

	Node* parent;

	sf::Vector2i state;

	sf::Vector2i action;

	Box* box;


	std::vector<sf::Vector2i> get_actions();
};
