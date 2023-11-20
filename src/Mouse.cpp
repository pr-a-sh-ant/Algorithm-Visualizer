#include <SFML/Graphics.hpp>
#include "Mouse.h"
#include <iostream>

// Box* Mouse::get_box(sf::Vector2i pos) const
// {
// 	// Readjust pos with starting of box
// 	pos.x -= this->box_starting_pos_.x;
// 	pos.y -= this->box_starting_pos_.y;

// 	if (pos.x < 0 || pos.y < 0 || pos.x > this->box_dim_.x * this->maze_dim_rows_cols_.x || pos.y > this->box_dim_.y *
// 		this->maze_dim_rows_cols_.y)
// 	{
// 		return nullptr;
// 	}


// 	int x = pos.x / this->box_dim_.x;
// 	x = x >= this->maze_dim_rows_cols_.x ? this->maze_dim_rows_cols_.x - 1 : x;

// 	int y = pos.y / this->box_dim_.y;
// 	y = y >= this->maze_dim_rows_cols_.y ? this->maze_dim_rows_cols_.y - 1 : y;

// 	return this->boxes_->at(x).at(y);
// }

void Mouse::update(sf::RenderWindow& window)
{
	this->pos = sf::Mouse::getPosition(window);
	// std::cout<<this->pos.x<<" "<<this->pos.y<<std::endl;
}
