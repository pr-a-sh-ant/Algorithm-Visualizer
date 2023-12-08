#include <iostream>
#include <SFML/Graphics.hpp>
#include "State.h"
#include "SearchWindow.h"

/*
int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Animation Engine");
	window.display();

	viz::anim::Animation animation(2.0f);
	animation.color = sf::Color::Blue;
	animation.scale = 10.0f;
	animation.reversing = true;
	animation.center_scale = true;

	sf::RectangleShape rect({20.0f, 20.0f});
	rect.setFillColor(sf::Color::Red);
	rect.setPosition({100.0f, 100.0f});
	viz::anim::AnimatableRectangle animatable_rect(rect, &animation);

	animatable_rect.start_animation();
	sf::Clock clock;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
		}

		animatable_rect.update(clock.restart().asSeconds());
		window.clear();
		window.draw(*animatable_rect.get_drawable());
		window.display();
	}
}*/

viz::State* viz::State::state_instance_ptr_ = nullptr;


int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Maze Solver", sf::Style::Fullscreen);
	sf::Clock clock;

	viz::window::SearchWindow search_window({ 1920, 1080 }, "Maze Solver");

	auto& state = viz::State::get_state_instance();
	float delta_time_seconds = 0.0f;


	while (window.isOpen())
	{
		sf::Event event;
		state.mouse.is_left_button_pressed = false;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case (sf::Event::Closed):
				window.close();
				break;
			case (sf::Event::KeyPressed):
				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}
				break;
			case (sf::Event::MouseButtonPressed):
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					state.mouse.is_left_button_down = true;
					state.mouse.is_left_button_pressed = true;
				}
				break;
			case (sf::Event::MouseButtonReleased):
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					state.mouse.is_left_button_down = false;
				}
				break;
			case (sf::Event::MouseMoved):
				state.update_mouse({ float(event.mouseMove.x), float(event.mouseMove.y) });
			default:
				break;
			}
		}
		
		delta_time_seconds = clock.restart().asSeconds();
		search_window.handle_state_change(state);

		window.clear();

		search_window.update(delta_time_seconds);
		search_window.draw(window);
		
		window.display();
	}
}


