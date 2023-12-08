#pragma once

#include "Window.h"
#include "Maze.h"

namespace viz::window
{
	class SearchWindow : public Window
	{
	private:
		inline static const sf::Vector2f maze_position = { 0, 0 }; // Top left corner of the maze
		inline static const sf::Vector2i maze_size_boxes = {40, 40}; // Boxes in the maze
		inline static const sf::Vector2f maze_box_dimensions = {26, 26}; // Pixels per box

		void init_buttons();
		void handle_state_change_button(viz::State& state) override;
		void update_button(const float delta_time_seconds) override;
		void draw_button(sf::RenderWindow& window) override;
	public:
		viz::Maze* maze;

		SearchWindow(const sf::Vector2u& window_size, const std::string& title);
		~SearchWindow() override;

		void draw(sf::RenderWindow& window) override;
		void update(const float delta_time_seconds) override;
		void handle_state_change(viz::State& state) override;
	};
}