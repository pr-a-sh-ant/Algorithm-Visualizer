#include <SFML/Graphics.hpp>
#include "Node.h"
#include "Box.h"
#include <iostream>


Node::Node(sf::Vector2i state, Node* parent, sf::Vector2i action, Box* box)
{
	this->parent = parent;
	this->action = action;
	this->box = box;
	this->state = state;
	
}

Node::Node(sf::Vector2i state, Box* box)
{
	this->box = box;
	this->state = state;
}

std::vector<sf::Vector2i> Node::get_actions()
{
	std::vector<sf::Vector2i> actions;
	std::vector<sf::Vector2i> dels = {
		sf::Vector2i(0, 1),
		sf::Vector2i(1, 0),
		sf::Vector2i(-1, 0),
		sf::Vector2i(0, -1),
	};


	for (unsigned int a = 0; a < dels.size(); a++)
	{
		int xpos = state.x + dels[a].x;
		int ypos = state.y + dels[a].y;

		if (xpos >= 0 && ypos >= 0 && xpos < 40 && ypos < 40)
		{
			actions.push_back(sf::Vector2i(xpos, ypos));
		}
	}

	return actions;
}
