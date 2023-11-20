#include "Animation.h"

viz::anim::Animation::Animation(const sf::Vector2f& displacement, const float& scale, const float& time, const bool reversing)
	: displacement(displacement), time(time), scale(scale), reversing(reversing)
{
}

viz::anim::Animation::Animation(const sf::Vector2f& displacement, const float& time, const bool reversing)
	: displacement(displacement), time(time), scale(0), reversing(reversing)
{
}

viz::anim::Animation::Animation(const float& scale, const float& time, const bool reversing)
	: displacement(sf::Vector2f(0, 0)), time(time), scale(scale), reversing(reversing)
{
}

