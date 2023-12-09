#pragma once

#include "Window.h"

namespace viz::window
{
	class HomeWindow : public Window
	{
		void init_buttons();
		void handle_state_change_button(viz::State& state) override;
		void update_button(const float delta_time_seconds) override;
		void draw_button(sf::RenderWindow& window) override;
	public:
		sf::Texture background_texture;
		sf::RectangleShape background;
		std::function<void()> search_call_back;
		std::function<void()> sort_call_back;

		HomeWindow(const sf::Vector2u& window_size, std::string title ,std::function<void()> search_call_back, std::function<void()> sort_call_back);

		void reset() override;
		void draw(sf::RenderWindow& window) override;
		void update(const float delta_time_seconds) override;
		void handle_state_change(viz::State& state) override;
	};
}