#include <SFML/Graphics.hpp>
#include "MazeBox.h"
#include "Animation.h"

sf::Color viz::MazeBox::get_box_color(MazeBoxType type)
{
	return MazeBox::box_colors[static_cast<int>(type)];
}

viz::MazeBox::MazeBox(const sf::RectangleShape& sample_rect, const MazeBoxType type)
	: animatable_rectangle_(sample_rect)
{
	this->set_type(type, true);
}

viz::MazeBoxType viz::MazeBox::get_type() const
{
	return this->type_;
}

const sf::Drawable* viz::MazeBox::get_drawable() const
{
	return this->animatable_rectangle_.get_drawable();
}

bool viz::MazeBox::is_animating() const
{
	return this->animatable_rectangle_.is_animating();
}

void viz::MazeBox::set_type(const MazeBoxType type, const bool animate)
{
	this->type_ = type;
	if (this->animatable_rectangle_.is_animating())
	{
		this->animatable_rectangle_.stop_animation_and_reset();
	}
	this->animatable_rectangle_.change_rectangle_color(MazeBox::get_box_color(type));

	switch (type)
	{
	case MazeBoxType::searched:
		this->animatable_rectangle_.set_animation(&MazeBox::search_animation);
		if (animate) this->animatable_rectangle_.start_animation();
		break;
	case MazeBoxType::path:
		this->animatable_rectangle_.set_animation(&MazeBox::found_animation);
		if (animate) this->animatable_rectangle_.start_animation();
		break;
	default:
			break;
	}
}

void viz::MazeBox::set_position(const sf::Vector2f& position)
{
	this->animatable_rectangle_.set_position(position);
}

void viz::MazeBox::update_animation(const float& delta_time_seconds)
{
	this->animatable_rectangle_.update(delta_time_seconds);
}
