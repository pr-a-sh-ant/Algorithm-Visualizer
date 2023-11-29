#include "Algorithm.h"
#include "Node.h"
#include <iostream>

Algorithm::Algorithm()
{
}

Node* Algorithm::remove()
{
	if (empty())
	{
		std::cout << "EMPTY FRONTIER" << std::endl;
		
	}
	else
	{
		Node *node = frontier[0];
		frontier.erase(frontier.begin());
		return node;
	}
}

bool Algorithm::empty()
{
	return frontier.size() == 0;
}

void Algorithm::add(Node *node)
{
	frontier.push_back(node);
}

bool Algorithm::contains_state(sf::Vector2i state)
{
	for (unsigned x = 0; x < frontier.size(); x++)
	{
		if (state == frontier[x]->state)
		{
			return true;
		}
	}
	return false;
}

bool Algorithm::inExplored(sf::Vector2i state)
{
	for (unsigned x = 0; x < explored.size(); x++)
	{
		if (state == explored[x])
		{
			return true;
		}
	}
	return false;
}

void Algorithm::reset(){

	frontier.clear();
	explored.clear();


}