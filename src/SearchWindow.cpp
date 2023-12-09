#include "SearchWindow.h"

#include <iostream>
// include standard exception
#include <stdexcept>
#include "State.h"

#pragma region button_callback_functions
namespace search_callbacks
{
	void recursiveDivision(std::vector<std::vector<int>>& maze, int startRow, int endRow, int startCol, int endCol) {
    if (startRow + 1 >= endRow || startCol + 1 >= endCol) {
        return;
    }

    // Choose a random point to create a passage
    int wallRow = rand() % (endRow - startRow - 1) + startRow + 1;
    int wallCol = rand() % (endCol - startCol - 1) + startCol + 1;

    // Create a horizontal passage
    for (int col = startCol; col <= endCol; ++col) {
        maze[wallRow][col] = 0;
    }

    // Create a vertical passage
    for (int row = startRow; row <= endRow; ++row) {
        maze[row][wallCol] = 0;
    }

    // Create three more walls to divide the maze into four chambers
    recursiveDivision(maze, startRow, wallRow - 1, startCol, wallCol - 1);  // Top-left chamber
    recursiveDivision(maze, startRow, wallRow - 1, wallCol + 1, endCol);     // Top-right chamber
    recursiveDivision(maze, wallRow + 1, endRow, startCol, wallCol - 1);     // Bottom-left chamber
    recursiveDivision(maze, wallRow + 1, endRow, wallCol + 1, endCol);        // Bottom-right chamber
}

	void back(viz::window::SearchWindow &search_window)
	{
		search_window.back_callback();
	}

	void maze(viz::window::SearchWindow &search_window)
	{
		auto &state = viz::State::get_state_instance();
		state.search.mouse_click_mode = viz::search_mouse_click_mode::wall;
	}

	void destination(viz::window::SearchWindow &search_window)
	{
		auto &state = viz::State::get_state_instance();
		state.search.mouse_click_mode = viz::search_mouse_click_mode::goal;
	}

	void start_point(viz::window::SearchWindow &search_window)
	{
		auto &state = viz::State::get_state_instance();
		state.search.mouse_click_mode = viz::search_mouse_click_mode::start;
	}

	void search(viz::window::SearchWindow &search_window)
	{
		if (viz::State::get_state_instance().search.visualizer_mode != viz::search_visualizer_mode::none)
		{
			return;
		}
		search_window.maze->clear();
		search_window.selected_search_algorithm->reset();
		search_window.selected_search_algorithm->start_search();
	}

	void bfs(viz::window::SearchWindow &search_window)
	{
		search_window.selected_search_algorithm = search_window.search_algorithms["BreadthFirstSearch"];
		search_window.maze->clear();
		search_window.selected_search_algorithm->reset();
	}

	void dfs(viz::window::SearchWindow &search_window)
	{
		search_window.selected_search_algorithm = search_window.search_algorithms["DepthFirstSearch"];
		search_window.maze->clear();
		search_window.selected_search_algorithm->reset();
	}

	void clearMaze(viz::window::SearchWindow &search_window)
	{
		search_window.maze->clear();
		search_window.selected_search_algorithm->reset();	
		search_window.maze->reset();
		viz::State::get_state_instance().search.visualizer_mode = viz::search_visualizer_mode::none;
	}
	void generate_maze(viz::window::SearchWindow& search_window){

		
		clearMaze(search_window);
		
		std::vector<std::vector<int>> maze_ko_tauko(search_window.maze->get_boxes_in_maze().x, std::vector<int>(search_window.maze->get_boxes_in_maze().y, 1));
		recursiveDivision(maze_ko_tauko, 0, search_window.maze->get_boxes_in_maze().x - 1, 0, search_window.maze->get_boxes_in_maze().y - 1);

		for(int x=0;x<maze_ko_tauko.size();x++)	
			{
				for(int y=0;y<maze_ko_tauko[x].size();y++)
				{

						std::cout<<x<<","<<y<<std::endl;
						if(maze_ko_tauko[x][y] == 1){
							search_window.maze->set_wall({x,y});				
						}

				}	
			}

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
	void (*callback)(viz::window::SearchWindow &search_window);
};

void viz::window::SearchWindow::init_buttons()
{
	const std::vector<ButtonInfo> button_info = {
		{{1400, 950}, {200, 80}, "Back", {204, 0, 0}, {255, 0, 0}, search_callbacks::back},	  // Back Button
		{{1550, 50}, {300, 80}, "Maze", {9, 57, 120}, {19, 98, 168}, search_callbacks::maze}, // Maze Button
		{{1550, 150}, {300, 80}, "Destination", {9, 57, 120}, {19, 98, 168}, search_callbacks::destination},
		// Destination Button
		{{1150, 150}, {300, 80}, "Start Point", {9, 57, 120}, {19, 98, 168}, search_callbacks::start_point},
		// Start Point Button
		{{1150, 50}, {300, 80}, "Search", {58, 107, 102}, {116, 216, 143}, search_callbacks::search},		 // Search Button
		{{1150, 250}, {300, 80}, "Clear", {9, 57, 120}, {19, 98, 168}, search_callbacks::clearMaze},		 // Clear Button
		{{1400, 550}, {200, 80}, "BFS", {9, 57, 120}, {19, 98, 168}, search_callbacks::bfs},				 // BFS Button
		{{1400, 650}, {200, 80}, "DFS", {9, 57, 120}, {19, 98, 168}, search_callbacks::dfs},				 // DFS Button
		{{1550, 250}, {300, 80}, "Generate Maze", {9, 57, 120}, {19, 98, 168}, search_callbacks::generate_maze}, // Generate Maze Button
	};
	const std::string font_path = "Public/font.ttf";

	for (const auto &info : button_info)
	{
		this->buttons_.push_back(new Button(info.position, info.dimensions, info.text, font_path, info.fill_color,
											info.fill_color_hover,
											[this, info]()
											{ info.callback(std::ref(*this)); }));
	}
}

void viz::window::SearchWindow::handle_state_change_button(State &state)
{
	for (const auto &button : this->buttons_)
	{
		button->handle_mouse(state.mouse);
	}
}

void viz::window::SearchWindow::update_button(const float delta_time_seconds)
{
	for (const auto &button : this->buttons_)
	{
		button->update();
	}
}

void viz::window::SearchWindow::draw_button(sf::RenderWindow &window)
{
	for (const auto &button : this->buttons_)
	{
		button->draw(window);
	}
}

viz::window::SearchWindow::SearchWindow(const sf::Vector2u &window_size, const std::string &title, std::function<void()> back_callback)
	: Window(window_size, title), back_callback(std::move(back_callback))
{
	this->maze = new Maze(maze_box_dimensions, maze_size_boxes, maze_position);
	this->search_space = new search::SearchSpace(this->maze);
	this->search_algorithms = {
		{"BreadthFirstSearch", new search::BreadthFirstSearch(this->search_space, 0.01f)},
		{"DepthFirstSearch", new search::DepthFirstSearch(this->search_space, 0.01f)},
	};
	this->selected_search_algorithm = this->search_algorithms["BreadthFirstSearch"]; // Set BFS as default
	this->init_buttons();															 // initialize the buttons
	// Setup text
	this->algorithm_text = sf::Text("Algorithm", this->buttons_.front()->font, 60);
	algorithm_text.setPosition(1350, 450);
}

viz::window::SearchWindow::~SearchWindow()
{
	delete this->maze;
	delete this->search_space;

	// delete all the algorithms in this->search_algorithms
	for (auto &[name, algorithm] : this->search_algorithms)
	{
		delete algorithm;
	}
}

void viz::window::SearchWindow::reset()
{
	this->maze->clear();
	this->selected_search_algorithm->reset();
}

void viz::window::SearchWindow::draw(sf::RenderWindow &window)
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

void viz::window::SearchWindow::handle_state_change(State &state)
{
	this->handle_state_change_button(state);
	this->maze->handle_state_change(state);
}
