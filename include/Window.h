#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "State.h"
#include "Button.h"

namespace viz::window
{
	class Window
	{
	protected:
		std::string title_;	// Title of the window
		sf::Vector2u window_size_;	// Size of the window

		std::vector<viz::Button*> buttons_;	// Buttons that are drawn on the window
		virtual void handle_state_change_button(viz::State& state) = 0;
		virtual void update_button(const float delta_time_seconds) = 0;
		virtual void draw_button(sf::RenderWindow& window) = 0;
	public:
		explicit Window(const sf::Vector2u& window_size ,std::string title); // Constructor
		virtual ~Window();

		virtual void reset() = 0; // Reset the window
		virtual void draw(sf::RenderWindow& window) = 0; // Draw the window
		virtual void handle_state_change(viz::State& state) = 0; // Handle state change (eg. mouse move, click, etc.)
		virtual void update(const float delta_time_seconds) = 0; // Update the window and animations
	};
}