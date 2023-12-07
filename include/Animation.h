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
		bool center_scale;

		// Constructors
		Animation(const float time);
		// Parameterized Constructor
		Animation(const sf::Vector2f& displacement, const sf::Color& color, float time, float scale, bool reversing, bool center_scale);
		// Copy Constructor
		Animation(const Animation& other) = default;
	};

	class Animatable
	{
	protected:
		bool is_animating_; // Whether the object is currently animating
		const Animation* current_animation_; // Pointer to the current animation (not owned)
		float animation_clock_; // Time since animation started

	public:
		// Constructors
		Animatable();
		Animatable(const Animation* animation);
		// Destructor
		virtual ~Animatable();

		[[nodiscard]]
		bool is_animating() const;
		void set_animation(const Animation* animation);
		virtual void start_animation();

		virtual void set_position(const sf::Vector2f& position) = 0; // Sets the position of the object
		virtual void stop_animation_and_reset() = 0; // Stops the animation and resets the object to its initial state
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
		AnimatableRectangle(const sf::RectangleShape& rectangle, const Animation* animation);
		AnimatableRectangle(const sf::RectangleShape& rectangle);
		AnimatableRectangle(const sf::Vector2f& position, const sf::Vector2f& dimensions, const sf::Color& color, const Animation* animation);

		void set_position(const sf::Vector2f& position) override;
		void stop_animation_and_reset() override;
		void update(const float& delta_time_seconds) override;
		const sf::Drawable* get_drawable() const override;
		void start_animation() override;
		void change_rectangle_color(const sf::Color& color);
	};
}
