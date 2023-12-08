#include "Window.h"
#include <functional>

viz::window::Window::Window(const sf::Vector2u& window_size, std::string title)
	: title_(std::move(title)), window_size_(window_size)
{
}

viz::window::Window::~Window()
{
	for (const auto& button : this->buttons_)
	{
		delete button;
	}
}