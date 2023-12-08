#include "SearchWindow.h"

#include <iostream>
// include standard exception
#include <stdexcept>
#include "State.h"

#pragma region button_callback_functions
namespace search_callbacks
{
	void back(viz::window::SearchWindow& search_window)
	{
		throw std::runtime_error("Not Implemented");
		return;
	}

	void maze(viz::window::SearchWindow& search_window)
	{
		auto& state = viz::State::get_state_instance();
		state.search.mouse_click_mode = viz::search_mouse_click_mode::wall;
	}

	void destination(viz::window::SearchWindow& search_window)
	{
		auto& state = viz::State::get_state_instance();
		state.search.mouse_click_mode = viz::search_mouse_click_mode::goal;
	}

	void start_point(viz::window::SearchWindow& search_window)
	{
		auto& state = viz::State::get_state_instance();
		state.search.mouse_click_mode = viz::search_mouse_click_mode::start;
	}

	void search(viz::window::SearchWindow& search_window)
	{
		throw std::runtime_error("Not Implemented");
		return;
	}

	void clear(viz::window::SearchWindow& search_window)
	{
		throw std::runtime_error("Not Implemented");
		return;
	}

	void bfs(viz::window::SearchWindow& search_window)
	{
		throw std::runtime_error("Not Implemented");
		return;
	}

	void dfs(viz::window::SearchWindow& search_window)
	{
		throw std::runtime_error("Not Implemented");
		return;
	}
}
#pragma endregion

void viz::window::SearchWindow::init_buttons()
{
	// Back Button
	this->buttons_.push_back(new Button({0, 0}, {0, 0}, "Back", "Public/font.ttf", {0, 0, 0}, {0, 0, 0},
	                                    [this]() { search_callbacks::back(std::ref(*this)); }));
	// Maze Button
	this->buttons_.push_back(new Button({1600, 50}, {300, 80}, "Maze", "Public/font.ttf", {9, 57, 120}, {19, 98, 168},
	                                    [this]() { search_callbacks::maze(std::ref(*this)); }));
	// Destination Button
	this->buttons_.push_back(new Button({0, 0}, {0, 0}, "Destination", "Public/font.ttf", {0, 0, 0}, {0, 0, 0},
	                                    [this]() { search_callbacks::destination(std::ref(*this)); }));
	// Start Point Button
	this->buttons_.push_back(new Button({0, 0}, {0, 0}, "Start Point", "Public/font.ttf", {0, 0, 0}, {0, 0, 0},
	                                    [this]() { search_callbacks::start_point(std::ref(*this)); }));
	// Search Button
	this->buttons_.push_back(new Button({0, 0}, {0, 0}, "Search", "Public/font.ttf", {0, 0, 0}, {0, 0, 0},
	                                    [this]() { search_callbacks::search(std::ref(*this)); }));
	// Clear Button
	this->buttons_.push_back(new Button({0, 0}, {0, 0}, "Clear", "Public/font.ttf", {0, 0, 0}, {0, 0, 0},
	                                    [this]() { search_callbacks::clear(std::ref(*this)); }));
	// BFS Button
	this->buttons_.push_back(new Button({0, 0}, {0, 0}, "BFS", "Public/font.ttf", {0, 0, 0}, {0, 0, 0},
	                                    [this]() { search_callbacks::bfs(std::ref(*this)); }));
	// DFS Button
	this->buttons_.push_back(new Button({0, 0}, {0, 0}, "DFS", "Public/font.ttf", {0, 0, 0}, {0, 0, 0},
	                                    [this]() { search_callbacks::dfs(std::ref(*this)); }));
}

void viz::window::SearchWindow::handle_state_change_button(State& state)
{
	for (const auto& button : this->buttons_)
	{
		button->handle_mouse(state.mouse);
	}
}

void viz::window::SearchWindow::update_button(const float delta_time_seconds)
{
	for (const auto& button : this->buttons_)
	{
		button->update();
	}
}

void viz::window::SearchWindow::draw_button(sf::RenderWindow& window)
{
	for (const auto& button : this->buttons_)
	{
		button->draw(window);
	}
}

viz::window::SearchWindow::SearchWindow(const sf::Vector2u& window_size, const std::string& title)
	: Window(window_size, title)
{
	this->maze = new Maze(maze_box_dimensions, maze_size_boxes, maze_position);
	this->init_buttons();
}

viz::window::SearchWindow::~SearchWindow()
{
	delete this->maze;
}

void viz::window::SearchWindow::draw(sf::RenderWindow& window)
{
	this->draw_button(window);
	this->maze->draw_maze(window);
}

void viz::window::SearchWindow::update(const float delta_time_seconds)
{
	this->update_button(delta_time_seconds);
	this->maze->update_animation(delta_time_seconds);
}

void viz::window::SearchWindow::handle_state_change(viz::State& state)
{
	this->handle_state_change_button(state);
	this->maze->handle_state_change(state);
}
