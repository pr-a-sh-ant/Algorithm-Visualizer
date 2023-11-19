#pragma once

#include <SFML/Graphics.hpp>
// class App;

class Mouse
{

	public:
		sf::Vector2i pos;
		bool clicked;
private:
	sf::Vector2i maze_dim_rows_cols_;
	sf::Vector2i box_dim_;
	sf::Vector2i box_starting_pos_;

public:
	// Mouse();

	void update(sf::RenderWindow& window);
};
