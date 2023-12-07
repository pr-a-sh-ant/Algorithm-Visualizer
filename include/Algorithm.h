#pragma once
#include "Node.h"

class Algorithm

{
private:
	/* data */

public:
	Algorithm(/* args */);
	std::vector<Node*> frontier;
	std::vector<sf::Vector2i> explored;


	Node* remove();
	void add(Node *node);
	void contains_state();
	bool empty();
	bool contains_state(sf::Vector2i state);
	bool inExplored(sf::Vector2i state);
	void reset();
};
