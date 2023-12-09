#include "HomeWindow.h"

#include <iostream>

void viz::window::HomeWindow::init_buttons()
{
	this->buttons_.push_back(
		new Button({250, 650}, {500, 80}, "Search Algorithm", "Public/font.ttf", {9, 57, 120}, {19, 98, 168},
				   [this]()
				   { this->search_call_back(); }));
	this->buttons_.push_back(
		new Button({1200, 650}, {500, 80}, "Sort Algorithm", "Public/font.ttf", {9, 57, 120}, {19, 98, 168},
				   [this]()
				   { this->sort_call_back(); }));
	this->buttons_.push_back(
		new Button({850, 850}, {250, 80}, "Exit", "Public/font.ttf", {204, 0, 0}, {255, 0, 0},
				   [this]()
				   { this->exit_callback(); }));
}

void viz::window::HomeWindow::handle_state_change_button(State &state)
{
	for (const auto &button : this->buttons_)
	{
		button->handle_mouse(state.mouse);
	}
}

void viz::window::HomeWindow::update_button(const float delta_time_seconds)
{
	for (const auto &button : this->buttons_)
	{
		button->update();
	}
}

void viz::window::HomeWindow::draw_button(sf::RenderWindow &window)
{
	for (const auto &button : this->buttons_)
	{
		button->draw(window);
	}
}

viz::window::HomeWindow::HomeWindow(const sf::Vector2u &window_size, std::string title,
									std::function<void()> search_call_back, std::function<void()> sort_call_back, std::function<void()> exit_callback)
	: Window(window_size, std::move(title)), search_call_back(std::move(search_call_back)),
	  sort_call_back(std::move(sort_call_back)), exit_callback(std::move(exit_callback))
{
	this->init_buttons();
	if (!this->background_texture.loadFromFile("Public/start.jpg"))
	{
		throw std::runtime_error("Could not load background image");
	}
	this->background.setSize({1920, 1080});
	this->background.setTexture(&this->background_texture);
	this->background.setPosition(0, 0);
}

void viz::window::HomeWindow::reset()
{
}

void viz::window::HomeWindow::draw(sf::RenderWindow &window)
{
	window.draw(this->background);
	this->draw_button(window);
}

void viz::window::HomeWindow::update(const float delta_time_seconds)
{
	this->update_button(delta_time_seconds);
}

void viz::window::HomeWindow::handle_state_change(State &state)
{
	this->handle_state_change_button(state);
}
