#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Mouse.h"
#include "App.h"


class Box : public Entity
{
private:
	static inline sf::Color animColours[10] = {
		sf::Color{250, 0, 250},
		sf::Color{230, 0, 230},
		sf::Color{210, 0, 210},
		sf::Color{190, 0, 190},
		sf::Color{170, 0, 170},
		sf::Color{170, 0, 170},
		sf::Color{190, 0, 190},
		sf::Color{210, 0, 210},
		sf::Color{230, 0, 230},
		sf::Color{250, 0, 250}
	};

	static inline int scale[10] = {2, 4, 6, 8, 10, 10, 8, 6, 4, 2};

public:
	Box(int x, int y, int width, int height);
	sf::RectangleShape rect;
	void animate(float deltime);
	int currentAnimation = 0;
	float totalTime = 0.0f;
	float switchTIme = 0.05f;
	bool animating = false;
	void centerScale(int scale);
	void is_path();
	
	void update(App *app) override;
};
