#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "App.h"
#include "Maze.h"
#include "State.h"

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


int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Maze Solver");
	viz::Maze maze({28.0f, 28.0f}, {40, 40}, {10.0f, 10.0f});
	sf::Clock clock;

	auto& state = viz::State::get_state_instance();
	float delta_time_seconds = 0.0f;
	while (window.isOpen())
	{
		sf::Event event;
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
					state.update_mouse({ float(event.mouseButton.x), float(event.mouseButton.y) });
					maze.handle_event(event);
					state.mouse.is_left_button_down = true;
				}
			case (sf::Event::MouseButtonReleased):
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					state.mouse.is_left_button_down = false;
				}
				break;
			default:
				break;
			}
		}

		delta_time_seconds = clock.restart().asSeconds();

		window.clear();
		maze.update_animation(delta_time_seconds);
	}
}
