#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"

namespace viz
{
	// MazeBox types
	enum class MazeBoxType
	{
		empty = 0, // Default box type
		start, // Start box type
		goal,  // Goal box type
		obstacle, // Wall
		path, // Path
		searched // Searched MazeBox
	};

	// A box in the maze
	class MazeBox
	{
	private:
		// Animatable Rectangle of the box
		anim::AnimatableRectangle animatable_rectangle_;
		// Animation for searching
		static const inline anim::Animation search_animation = anim::Animation(
			{0, 0}, sf::Color{170, 0, 170}, 0.5f, 2.0f, true, true);
		// Animation for if the box is in the path
		static const inline anim::Animation found_animation = anim::Animation(
			{0, 0}, sf::Color{0, 0, 170}, 0.5f, 2.0f, true, true);
		// Colors for the box types
		static const inline sf::Color box_colors[6] = {
			sf::Color::Green, // Default box type
			sf::Color::Yellow, // Start box type
			sf::Color::Red,  // Goal box type,
			sf::Color::Black, // Wall
			sf::Color{0, 0, 250}, // Path
			sf::Color{250, 0, 250} // Searched MazeBox
		};
		// MazeBox type
		MazeBoxType type_;

	public:
		// Constructor
		MazeBox(const sf::RectangleShape& sample_rect, const MazeBoxType type = MazeBoxType::empty);
		// Delete the default constructor
		MazeBox() = delete;
		// Delete the copy constructor
		MazeBox(const MazeBox&);

		// Getters
		MazeBoxType get_type() const; // Returns the type of the current box
		const sf::Drawable* get_drawable() const; // Returns the drawable of the box to be drawn on the screen
		bool is_animating() const; // Returns true if the box is animating
		static sf::Color get_box_color(MazeBoxType type); // Returns the color of the box type
		// Setters
		void set_type(const MazeBoxType type, const bool animate = true); // Set the box type and start animation if needed and specified
		void set_position(const sf::Vector2f& position); // Set the position of the box

		// Updates the box animation
		void update_animation(const float& delta_time_seconds);
	};
}
