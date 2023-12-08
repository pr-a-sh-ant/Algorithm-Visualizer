#pragma once
#include <SFML/Graphics.hpp>
#include "MazeBox.h"

class Box;

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
	bool in_maze(std::vector<sf::Vector2i> maze);
};

namespace viz::search
{
	class Node
	{
	private:
		/* data */
	public:
		Node(sf::Vector2i state, std::shared_ptr<Node> parent);

		sf::Vector2i state;
		std::shared_ptr<Node> parent;
		bool visited;
	};
}
