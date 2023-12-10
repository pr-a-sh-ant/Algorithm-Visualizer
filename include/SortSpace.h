#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

namespace viz::sort
{
	class SortSpace
	{
	public:
		sf::Vector2f start_position;
		int box_min_height;
		int box_max_height;
		int box_width;
		int number_of_boxes;
		std::vector<int> box_heights;
		sf::RectangleShape background_box;
		sf::Vector2f bar_offset;

		SortSpace(const sf::Vector2f& start_position, const int box_min_height, const int box_max_height, const int box_width, const int number_of_boxes, const sf::Vector2f& bar_offset);
		~SortSpace() = default;

		// Sets the number of boxes
		void set_number_of_boxes(const int new_number_of_boxes);
		// Randomizes the box_heights vector
		void randomize();
		// Draws the boxes to the window
		void draw(sf::RenderWindow& window) const;
	};
}