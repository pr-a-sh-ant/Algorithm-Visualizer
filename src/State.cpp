#include "State.h"

viz::State* viz::State::state_instance_ptr_ = nullptr;

// Update the mouse position based on the input
void viz::State::update_mouse(const sf::Vector2i& mouse_position)
{
	this->mouse.prev_pos = this->mouse.pos;
	this->mouse.pos = {static_cast<float>(mouse_position.x), static_cast<float>(mouse_position.y)};
}
