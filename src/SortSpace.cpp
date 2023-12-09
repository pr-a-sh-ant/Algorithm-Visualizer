#include "SortSpace.h"

#include <random>
#include <algorithm>
#include <chrono>

// Thread safe random number generator
int get_random_number(const int min, const int max)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(min, max);
	return dis(gen);
}

viz::sort::SortSpace::SortSpace(const sf::Vector2f& start_position, const int box_min_height, const int box_max_height, const int box_width, const int number_of_boxes, const sf::Vector2f& bar_offset)
	: start_position(start_position), box_min_height(box_min_height), box_max_height(box_max_height), box_width(box_width), number_of_boxes(number_of_boxes), bar_offset(bar_offset)
{
	this->box_heights.resize(this->number_of_boxes);
	this->randomize();
	this->background_box.setFillColor(sf::Color::White);
	this->background_box.setSize(sf::Vector2f(static_cast<float>(this->box_width * this->number_of_boxes) + 20, static_cast<float>(this->box_max_height) + 20));
	this->background_box.setPosition(this->start_position);
}

void viz::sort::SortSpace::randomize()
{
	int single_difference = (this->box_max_height - this->box_min_height) / this->number_of_boxes;
	for (int i = 0;  i < this->box_heights.size(); i++)
	{
		this->box_heights[i] = this->box_min_height + (i * single_difference);
	}

	static const unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	// Shuffle the vector
	std::ranges::shuffle(this->box_heights.begin(), this->box_heights.end(), std::default_random_engine(seed));
}

void viz::sort::SortSpace::draw(sf::RenderWindow& window) const
{
	sf::RectangleShape bar;
	bar.setFillColor(sf::Color::Black);
	window.draw(this->background_box);

	for (int i = 0; i < this->number_of_boxes; i++)
	{
		bar.setSize(sf::Vector2f(static_cast<float>(this->box_width), static_cast<float>(this->box_heights[i])));
		bar.setPosition(this->start_position.x + this->bar_offset.x + static_cast<float>(i * this->box_width), this->start_position.y + this->bar_offset.y + static_cast<float>(this->box_max_height - this->box_heights[i]));

		window.draw(bar);
	}
}
