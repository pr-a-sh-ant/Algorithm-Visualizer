#include "Animation.h"
#include <iostream>

sf::Color calculate_color(const sf::Color& initial_color, const sf::Color& final_color, const float& progress)
{
	// TODO: Optimize this

	bool is_color_non_changing = (final_color == sf::Color{255, 255, 255, 0});
	if (is_color_non_changing)
	{
		return initial_color;
	}

	return initial_color + sf::Color{
		static_cast<sf::Uint8>(static_cast<float>(final_color.r - initial_color.r) * progress),
		static_cast<sf::Uint8>(static_cast<float>(final_color.g - initial_color.g) * progress),
		static_cast<sf::Uint8>(static_cast<float>(final_color.b - initial_color.b) * progress),
		static_cast<sf::Uint8>(static_cast<float>(final_color.a - initial_color.a) * progress)
	};
}

viz::anim::Animation::Animation(const float time)
	: displacement(sf::Vector2f(0, 0)), color({255, 255, 255, 0}), time(time), scale(0), reversing(false), center_scale(true)
{
}

viz::anim::Animation::Animation(const sf::Vector2f& displacement, const sf::Color& color, float time, float scale, bool reversing, bool center_scale)
	: displacement(displacement), color(color), time(time), scale(scale), reversing(reversing), center_scale(center_scale)
{
}

viz::anim::Animatable::Animatable()
	: is_animating_(false), current_animation_(nullptr), animation_clock_(0.0f)
{
}

viz::anim::Animatable::Animatable(const Animation* animation)
	: is_animating_(false), current_animation_(animation), animation_clock_(0.0f)
{
}

viz::anim::Animatable::~Animatable()
{
}

bool viz::anim::Animatable::is_animating() const
{
	return this->is_animating_;
}

void viz::anim::Animatable::set_animation(const Animation* animation)
{
	this->current_animation_ = animation;
}

void viz::anim::Animatable::start_animation()
{
	if (this->current_animation_ == nullptr)
	{
		throw std::runtime_error("Animation not set");
	}

	this->is_animating_ = true;
	this->animation_clock_ = 0.0f;
}

viz::anim::AnimatableRectangle::AnimatableRectangle(const sf::RectangleShape& rectangle, const Animation* animation)
	: Animatable(animation)
{
	this->rectangle_.setPosition(rectangle.getPosition());
	this->rectangle_.setSize(rectangle.getSize());
	this->rectangle_.setFillColor(rectangle.getFillColor());
	this->rectangle_.setOutlineColor(rectangle.getOutlineColor());
	this->rectangle_.setOutlineThickness(rectangle.getOutlineThickness());
}

viz::anim::AnimatableRectangle::AnimatableRectangle(const sf::RectangleShape& rectangle)
	: Animatable()
{
	this->rectangle_.setPosition(rectangle.getPosition());
	this->rectangle_.setSize(rectangle.getSize());
	this->rectangle_.setFillColor(rectangle.getFillColor());
	this->rectangle_.setOutlineColor(rectangle.getOutlineColor());
	this->rectangle_.setOutlineThickness(rectangle.getOutlineThickness());
}

viz::anim::AnimatableRectangle::AnimatableRectangle(const sf::Vector2f& position, const sf::Vector2f& dimensions, const sf::Color& color, const Animation* animation)
	: Animatable(animation), rectangle_(dimensions)
{
	this->rectangle_.setPosition(position);
	this->rectangle_.setFillColor(color);
}

void viz::anim::AnimatableRectangle::set_position(const sf::Vector2f& position)
{
	this->rectangle_.setPosition(position);
}

void viz::anim::AnimatableRectangle::stop_animation_and_reset()
{
	this->rectangle_.setPosition(this->initial_position_);
	this->rectangle_.setSize(this->initial_dimensions_);
	this->rectangle_.setFillColor(this->initial_color_);
	this->is_animating_ = false;
	this->animation_clock_ = 0.0f;
}

void viz::anim::AnimatableRectangle::update(const float& delta_time_seconds)
{
	// TODO: Optimize this
	// If not animating, do nothing
	if (!this->is_animating_)
	{
		return;
	}
	// Accumulate time
	this->animation_clock_ += delta_time_seconds;

	sf::Vector2f calculated_position;
	sf::Vector2f calculated_dimensions;
	sf::Color calculated_color;
	// If animation is over
	if (this->animation_clock_ >= this->current_animation_->time)
	{
		this->is_animating_ = false;
		// If animation is reversing, set to initial state
		if (this->current_animation_->reversing)
		{
			calculated_position = this->initial_position_;
			calculated_dimensions = this->initial_dimensions_;
			calculated_color = this->initial_color_;
		}
		// Else, set to final state
		else
		{
			calculated_position = this->initial_position_ + this->current_animation_->displacement;
			calculated_dimensions = this->initial_dimensions_ * this->current_animation_->scale;
			calculated_color = this->current_animation_->color;
		}
	}
	else
	{
		// If animation is reversing
		if (this->current_animation_->reversing)
		{
			// If animation is in first half
			if (this->animation_clock_ < this->current_animation_->time / 2.0f)
			{
				calculated_position = this->initial_position_ + this->current_animation_->displacement * this->
					animation_clock_ / (this->current_animation_->time / 2.0f);
				calculated_dimensions = this->initial_dimensions_ * (1.0f + (this->current_animation_->scale - 1.0f) *
					this->animation_clock_ / (this->current_animation_->time / 2.0f));
				calculated_color = calculate_color(this->initial_color_, this->current_animation_->color, this->
				                                   animation_clock_ / (this->current_animation_->time / 2.0f));
			}
			// Else, animation is in second half
			else
			{
				calculated_position = this->initial_position_ + this->current_animation_->displacement * (1.0f - (this->
					animation_clock_ -
					this->current_animation_->time / 2.0f) / (this->current_animation_->time / 2.0f));
				calculated_dimensions = this->initial_dimensions_ * (1.0f + (this->current_animation_->scale - 1.0f) * (
					1.0f - (this->
						animation_clock_ - this->current_animation_->time / 2.0f) / (this->current_animation_->time /
						2.0f)));
				calculated_color = calculate_color(this->initial_color_, this->current_animation_->color, 1.0f - (this->
					                                   animation_clock_ -
					                                   this->current_animation_->time / 2.0f) / (this->
					                                   current_animation_->time / 2.0f));
			}
		}
		// Else, animation is not reversing
		else
		{
			calculated_position = this->initial_position_ + this->current_animation_->displacement * this->
				animation_clock_ / this->current_animation_->time;
			calculated_dimensions = this->initial_dimensions_ * (1.0f + (this->current_animation_->scale - 1.0f) * this
				->
				animation_clock_ / this->current_animation_->time);
			calculated_color = calculate_color(this->initial_color_, this->current_animation_->color, this->
			                                   animation_clock_ / this->current_animation_->time);
		}
	}

	if (this->current_animation_->center_scale)
	{
		calculated_position -= (calculated_dimensions - this->initial_dimensions_) / 2.0f;
	}

	this->rectangle_.setPosition(calculated_position);
	this->rectangle_.setSize(calculated_dimensions);
	this->rectangle_.setFillColor(calculated_color);
}

const sf::Drawable* viz::anim::AnimatableRectangle::get_drawable() const
{
	return &this->rectangle_;
}

void viz::anim::AnimatableRectangle::start_animation()
{
	this->Animatable::start_animation();
	this->initial_dimensions_ = this->rectangle_.getSize();
	this->initial_position_ = this->rectangle_.getPosition();
	this->initial_color_ = this->rectangle_.getFillColor();
}

void viz::anim::AnimatableRectangle::change_rectangle_color(const sf::Color& color)
{
	this->rectangle_.setFillColor(color);
}
