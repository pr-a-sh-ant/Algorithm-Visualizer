#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Animation.h"

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

	static inline int scale[10] = {2, 4, 6, 8, 10, 10, 8, 6, 4, 2};

	// PP Code
	viz::anim::AnimatableRectangle animatable_rectangle_;
	static inline viz::anim::Animation search_animation_ = viz::anim::Animation({ 0, 0 }, sf::Color{170, 0, 170}, 0.5f, 2.0f, true, true);
	static inline viz::anim::Animation found_animation_ = viz::anim::Animation({ 0, 0 }, sf::Color{0, 0, 170}, 0.5f, 2.0f, true, true);

public:
	Box(int x, int y, const sf::RectangleShape& sample_rect, int width = 32, int height = 32, int type = 0);
	void animate(float deltime);
	int currentAnimation = 0;
	float totalTime = 0.0f;
	float switchTIme = 0.05f;
	bool animating = false;
	int type;
	void centerScale(int scale);
	void is_path();

	// PP Code
	const sf::Drawable* get_drawable();
};
