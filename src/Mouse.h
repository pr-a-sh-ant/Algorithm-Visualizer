#pragma once

#include "Box.h"

class Mouse
{
private:
	Box* get_box(sf::Vector2i pos) const;
	std::vector<std::vector<Box*>> *boxes_;
	sf::Vector2i maze_dim_rows_cols_;
	sf::Vector2i box_dim_;
	sf::Vector2i box_starting_pos_;

public:
	Mouse(std::vector<std::vector<Box*>>& boxes);

	void update(const sf::RenderWindow& window) const;
};
