#include <SFML/Graphics.hpp>
#include "Animation.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Animation Engine");
	window.display();

	viz::anim::Animation animation(2.0f);
	animation.color = sf::Color::Blue;
	animation.displacement = {100.0f, 100.0f};
	animation.scale = 2.0f;
	animation.reversing = true;

	sf::RectangleShape rect({20.0f, 20.0f});
	rect.setFillColor(sf::Color::Red);
	rect.setPosition({10.0f, 10.0f});
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
}
