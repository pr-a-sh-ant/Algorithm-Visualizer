#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

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
	static inline sf::Color animColours2[10] = {
		sf::Color{0, 0, 250},
		sf::Color{0, 0, 230},
		sf::Color{0, 0, 210},
		sf::Color{0, 0, 190},
		sf::Color{0, 0, 170},
		sf::Color{0, 0, 170},
		sf::Color{0, 0, 190},
		sf::Color{0, 0, 210},
		sf::Color{0, 0, 230},
		sf::Color{0, 0, 250}
	};
	static inline float switchTIme = 0.05f;

	static inline int scale[10] = {2, 4, 6, 8, 10, 10, 8, 6, 4, 2};

public:
	Box(int x, int y, int width, int height,int type);
	void animate(float deltime);
	int currentAnimation = 0;
	float totalTime = 0.0f;
	bool animating = false;
	int type;
	void centerScale(int scale);
	void is_path();

	static void changeSwitchTime(float time){
		switchTIme = time;
	}
};

