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
		if (viz::State::get_state_instance().search.visualizer_mode != viz::search_visualizer_mode::none)
		{
			return;
		}
		search_window.maze->clear();
		search_window.selected_search_algorithm->reset();
		search_window.selected_search_algorithm->start_search();
	}

	void clear(viz::window::SearchWindow& search_window)
	{
		search_window.maze->clear();
		search_window.selected_search_algorithm->reset();
		viz::State::get_state_instance().search.visualizer_mode = viz::search_visualizer_mode::none;
	}

	void bfs(viz::window::SearchWindow& search_window)
	{
		search_window.selected_search_algorithm = search_window.search_algorithms["BreadthFirstSearch"];
		search_window.maze->clear();
		search_window.selected_search_algorithm->reset();
	}

	void dfs(viz::window::SearchWindow& search_window)
	{
		search_window.selected_search_algorithm = search_window.search_algorithms["DepthFirstSearch"];
		search_window.maze->clear();
		search_window.selected_search_algorithm->reset();
	}
}
#pragma endregion

struct ButtonInfo
{
	sf::Vector2f position;
	sf::Vector2f dimensions;
	std::string text;
	sf::Color fill_color;
	sf::Color fill_color_hover;
	void (*callback)(viz::window::SearchWindow& search_window);
};

void viz::window::SearchWindow::init_buttons()
{
	const std::vector<ButtonInfo> button_info = {
		{{1400, 900}, {200, 80}, "Back", {9, 57, 120}, {0, 0, 0}, search_callbacks::back}, // Back Button
		{{1600, 50}, {300, 80}, "Maze", {9, 57, 120}, {19, 98, 168}, search_callbacks::maze}, // Maze Button
		{{1600, 150}, {300, 80}, "Destination", {9, 57, 120}, {0, 0, 0}, search_callbacks::destination},
		// Destination Button
		{{1200, 150}, {300, 80}, "Start Point", {9, 57, 120}, {0, 0, 0}, search_callbacks::start_point},
		// Start Point Button
		{{1200, 50}, {300, 80}, "Search", {9, 57, 120}, {19, 98, 168}, search_callbacks::search}, // Search Button
		{{1450, 250}, {200, 80}, "Clear", {9, 57, 120}, {0, 0, 0}, search_callbacks::clear}, // Clear Button
		{{1450, 450}, {200, 80}, "BFS", {9, 57, 120}, {0, 0, 0}, search_callbacks::bfs}, // BFS Button
		{{1450, 550}, {200, 80}, "DFS", {9, 57, 120}, {0, 0, 0}, search_callbacks::dfs}, // DFS Button
	};
	const std::string font_path = "Public/font.ttf";

	for (const auto& info : button_info)
	{
		this->buttons_.push_back(new Button(info.position, info.dimensions, info.text, font_path, info.fill_color,
		                                    info.fill_color_hover,
		                                    [this, info]() { info.callback(std::ref(*this)); }));
	}
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
	this->search_space = new search::SearchSpace(this->maze);
	this->search_algorithms = {
		{"BreadthFirstSearch", new search::BreadthFirstSearch(this->search_space, 0.01f)},
		{"DepthFirstSearch", new search::DepthFirstSearch(this->search_space, 0.01f)},
	};
	this->selected_search_algorithm = this->search_algorithms["BreadthFirstSearch"]; // Set BFS as default
	this->init_buttons();	// initialize the buttons
	// Setup text
	this->algorithm_text = sf::Text("Algorithm", this->buttons_.front()->font, 60);
	algorithm_text.setPosition(1400, 350);
}

viz::window::SearchWindow::~SearchWindow()
{
	delete this->maze;
	delete this->search_space;

	// delete all the algorithms in this->search_algorithms
	for (auto& [name, algorithm] : this->search_algorithms)
	{
		delete algorithm;
	}
}

void viz::window::SearchWindow::draw(sf::RenderWindow& window)
{
	window.draw(this->algorithm_text);
	this->draw_button(window);
	this->maze->draw_maze(window);
}

void viz::window::SearchWindow::update(const float delta_time_seconds)
{
	this->update_button(delta_time_seconds);
	this->maze->update_animation(delta_time_seconds);
	this->selected_search_algorithm->update(delta_time_seconds);
}

void viz::window::SearchWindow::handle_state_change(State& state)
{
	this->handle_state_change_button(state);
	this->maze->handle_state_change(state);
}
