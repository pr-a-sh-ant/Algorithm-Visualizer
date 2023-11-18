#include <SFML/Graphics.hpp>
#include "Mouse.h"
#include <iostream>

Box* Mouse::get_box(sf::Vector2i pos) const
{
	// Readjust pos with starting of box
	pos.x -= this->box_starting_pos_.x;
	pos.y -= this->box_starting_pos_.y;

	if (pos.x < 0 || pos.y < 0 || pos.x > this->box_dim_.x * this->maze_dim_rows_cols_.x || pos.y > this->box_dim_.y *
		this->maze_dim_rows_cols_.y)
	{
		return nullptr;
	}


	int x = pos.x / this->box_dim_.x;
	x = x >= this->maze_dim_rows_cols_.x ? this->maze_dim_rows_cols_.x - 1 : x;

	int y = pos.y / this->box_dim_.y;
	y = y >= this->maze_dim_rows_cols_.y ? this->maze_dim_rows_cols_.y - 1 : y;

	return this->boxes_->at(x).at(y);
}

Mouse::Mouse(std::vector<std::vector<Box*>>& boxes)
{
	this->boxes_ = &boxes;
	this->maze_dim_rows_cols_ = sf::Vector2i(boxes.size(), boxes[0].size());
	this->box_dim_ = sf::Vector2i(boxes[0][0]->dim.x, boxes[0][0]->dim.y);
	this->box_starting_pos_ = sf::Vector2i(boxes[0][0]->pos.x, boxes[0][0]->pos.y);
}

void Mouse::update(const sf::RenderWindow& window) const
{
	const sf::Vector2i pos = sf::Mouse::getPosition(window);
	std::cout<<pos.x<<" "<<pos.y<<std::endl;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		// calculate the box that the mouse is over
		const auto box = this->get_box(pos);
		if (!box)
		{
			return;
		}

		box->animating = true;
	}
}
