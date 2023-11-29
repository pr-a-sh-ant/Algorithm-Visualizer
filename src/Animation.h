#pragma once

#include <SFML/Graphics.hpp>

namespace viz::anim
{
	class Animation
	{
	public:
		sf::Vector2f displacement;
		sf::Color color;
		float time;
		float scale;
		bool reversing;

		// Constructors
		Animation(const float time);
		// Copy Constructor
		Animation(const Animation& other) = default;

	};

	class Animatable
	{
	protected:
		bool is_animating_; // Whether the object is currently animating
		Animation* current_animation_; // Pointer to the current animation (not owned)
		float animation_clock_; // Time since animation started

	public:
		// Constructors
		Animatable();
		Animatable(Animation* animation);
		// Destructor
		virtual ~Animatable();

		[[nodiscard]]
		bool is_animating() const;
		void set_animation(Animation* animation);
		virtual void start_animation();

		virtual void update(const float& delta_time_seconds) = 0; // Updates the animation
		virtual const sf::Drawable* get_drawable() const = 0; // Returns a pointer to the drawable object
	};

	class AnimatableRectangle: public Animatable
	{
	private:
		sf::RectangleShape rectangle_; // The rectangle to be animated
		sf::Vector2f initial_position_; // The initial position of the rectangle
		sf::Vector2f initial_dimensions_; // The initial dimensions of the rectangle
		sf::Color initial_color_; // The initial color of the rectangle

	public:
		// Constructors
		AnimatableRectangle(sf::RectangleShape rectangle, Animation* animation);
		AnimatableRectangle(sf::RectangleShape rectangle);

		void update(const float& delta_time_seconds) override;
		const sf::Drawable* get_drawable() const override;
		void start_animation() override;
	};
}
