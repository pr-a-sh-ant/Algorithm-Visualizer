#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <functional>
#include <map>

#include "Window.h"
#include "SortSpace.h"
#include "Sort.h"

namespace viz::window
{
	class SortWindow : public viz::window::Window
	{
	public:
		inline static const sf::Vector2f sort_space_start_position = sf::Vector2f(10.0f, 10.0f); // Start position of the sort space
		inline static const sf::Vector2f bars_offset = sf::Vector2f(10.0f, 10.0f);				 // Offset of the bars
		constexpr static const int number_of_bars = 100;										 // Number of bars
		constexpr static const int bar_min_height = 10;											 // Minimum height of a bar
		constexpr static const int bar_max_height = 1010;										 // Maximum height of a bar
		constexpr static const int bounding_rect_width = 1020;									 // Width of the bounding rectangle
		constexpr static const float step_delay = 0.005f;										 // Delay between steps
		int bar_width;																			 // Width of a bar

		void init_buttons();
		void handle_state_change_button(viz::State &state) override;
		void update_button(const float delta_time_seconds) override;
		void draw_button(sf::RenderWindow &window) override;

	public:
		SortWindow(const sf::Vector2u &window_size, const std::string &title, std::function<void()> back_callback);
		~SortWindow() override;

		std::map<std::string, viz::sort::Sort *> sort_algorithms; // Map of sort algorithms
		viz::sort::Sort *selected_sort_algorithm;				  // Pointer to the current sort algorithm

		std::function<void()> back_callback; // Callback to go back to the main menu

		viz::sort::SortSpace *sort_space; // Pointer to the sort space

		sf::Text sort_text;

		void reset() override;
		void draw(sf::RenderWindow &window) override;
		void update(const float delta_time_seconds) override;
		void handle_state_change(viz::State &state) override;
	};
}