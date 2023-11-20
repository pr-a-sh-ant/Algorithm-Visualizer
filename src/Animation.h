#pragma once

#include <SFML/Graphics.hpp>

namespace viz::anim
{
	class Animation
	{
	public:
		sf::Vector2f displacement;
		float time;
		float scale;
		bool reversing;

		// Constructors
		Animation() = default;
		Animation(const sf::Vector2f& displacement, const float& scale, const float& time, const bool reversing = false);
		Animation(const sf::Vector2f& displacement, const float& time, const bool reversing = false);
		Animation(const float& scale, const float& time, const bool reversing = false);
		// Copy Constructor
		Animation(const Animation& other) = default;
	};

	class Animatable
	{
	protected:
		bool is_animating_;
		Animation* current_animation_;

	public:
		// Constructors
		Animatable();
		Animatable(Animation* animation);

		bool is_animating() const;
		void set_animation(Animation* animation);

		virtual void update(const float& delta_time) = 0;
		virtual sf::Drawable* get_drawable() = 0;
	};

	class AnimatableRectangle: public Animatable
	{
	private:

	};
}
