#include "Search.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "App.h"

Box *Search::get_box(sf::Vector2i &pos)
{
	return this->box[pos.x][pos.y];
}

Search::Search(App *app)
{
	this->app = app;
	textAlgo = new sf::Text("Alogrithms", this->app->font, 60);
	init();
}

void Search::init()
{
	this->textAlgo->setPosition(1350, 350);

	init_boxes();
	init_solve();
	init_buttons();
}

void Search::init_solve()
{
	search_complete = false;
	searching = false;
	maze.clear();
	visited.clear();
	parents.clear();
	queue.empty();

	sf::Vector2i temp = {-1, -1};

	for (int x = 0; x < this->boxOrder; x++)
	{
		std::vector<bool> visited_temp;
		std::vector<sf::Vector2i> parents_temp;
		for (int y = 0; y < this->boxOrder; y++)
		{
			visited_temp.emplace_back(false);
			parents_temp.emplace_back(temp);
		}
		this->parents.emplace_back(parents_temp);
		this->visited.emplace_back(visited_temp);
	}
}

void Search::init_boxes()
{
	for (int x = 0; x < this->boxOrder; x++)
	{
		std::vector<Box *> temp_box;
		for (int y = 0; y < this->boxOrder; y++)
		{
			temp_box.push_back(new Box(origin.x + (x * matrix_width), origin.y + (y * matrix_height), matrix_width, matrix_height, 0));
		}
		box.push_back(temp_box);
	}
}

void Search::init_buttons()
{
	this->buttons.push_back(new Button(1400, 980, "Back", 200, 80, "goBack"));
	this->buttons.push_back(new Button(1550, 50, "Maze", 300, 80, "modeMaze"));
	this->buttons.push_back(new Button(1550, 150, "Destination", 300, 80, "modeDestination"));
	this->buttons.push_back(new Button(1150, 150, "Start Point", 300, 80, "modeStart"));
	this->buttons.push_back(new Button(1150, 50, "Search", 300, 80, "setSearching"));
	this->buttons.push_back(new Button(1350, 250, "Clear", 300, 80, "setSearching"));
}

void Search::update()
{

	totalTime += this->app->deltime;

	if (this->app->appState->startSearch == 1)
	{
		searching = true;
	}

	if (searching)
	{
		solve();
		totalTime = 0;
	}
	update_boxes();
	update_buttons();
}

void Search::update_boxes()
{

	for (int i = 0; i < maze.size(); i++)
	{
		box[maze[i].x][maze[i].y]->rect.setFillColor(sf::Color::Black);
	}

	for (int x = 0; x < this->boxOrder; x++)
	{
		for (int y = 0; y < this->boxOrder; y++)
		{
			if (sf::Vector2i(x, y) == initial_state)
			{

				box[x][y]->rect.setFillColor(sf::Color{250, 100, 150});
			}
			else if (sf::Vector2i(x, y) == final_state)
			{
				box[x][y]->rect.setFillColor(sf::Color{250, 0, 0});
			}
			else if (box[x][y]->type == -1)
			{
				box[x][y]->rect.setFillColor(sf::Color::Black);
			}
			else if (box[x][y]->type == -3)
			{
				box[x][y]->rect.setFillColor(sf::Color::Magenta);
			}
			if (box[x][y]->animating)
			{
				box[x][y]->animate(this->app->deltime);
			}

			if (this->app->appState->mode == 0)
			{
				// std::cout<<"MODE 0 : MAZE MODE"<<std::endl;
				if (box[x][y]->mouse_over(this->app->mouse->pos) && this->app->mouse->clicked)
				{
					std::cout << "Set Box As Maze " << std::endl;
					box[x][y]->type = -1;
					box[x][y]->rect.setFillColor(sf::Color::Green);
				}
			}

			else if (this->app->appState->mode == 1)
			{
				// std::cout<<"MODE 1 : START MODE"<<std::endl;
				if (box[x][y]->mouse_over(this->app->mouse->pos) && this->app->mouse->clicked)
				{
					box[this->final_state.x][this->final_state.y]->rect.setFillColor(sf::Color::Green);
					box[this->final_state.x][this->final_state.y]->type = 0;
					this->final_state = sf::Vector2i(x, y);
					box[x][y]->type = 1;
				}
			}

			else if (this->app->appState->mode == 2)
			{
				// std::cout<<"MODE 2 : FInal MODE"<<std::endl;
				if (box[x][y]->mouse_over(this->app->mouse->pos) && this->app->mouse->clicked)
				{
					box[this->initial_state.x][this->initial_state.y]->rect.setFillColor(sf::Color::Green);
					box[this->initial_state.x][this->initial_state.y]->type = 0;
					this->initial_state = sf::Vector2i(x, y);
					box[x][y]->type = 2;
				}
			}
		}
	}
}

void Search::update_buttons()
{

	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i]->update(this->app->mouse, this->app->appState);
	}
}

void Search::draw_buttons()
{
	for (int i = 0; i < buttons.size(); i++)
	{

		buttons[i]->draw(this->app->window);
	}
}

void Search::draw_boxes()
{
	// Draw
	for (int x = 0; x < this->boxOrder; x++)
	{
		for (int y = 0; y < this->boxOrder; y++)
		{
			if (!box[x][y]->animating)
				app->window->draw(box[x][y]->rect);
		}
	}
	for (int x = 0; x < this->boxOrder; x++)
	{
		for (int y = 0; y < this->boxOrder; y++)
		{
			if (box[x][y]->animating)
				app->window->draw(box[x][y]->rect);
		}
	}
}

void Search::draw()
{
	this->app->window->draw(*this->textAlgo);
	draw_boxes();
	draw_buttons();
}

void Search::solve()
{

	if (this->queue.front() == this->final_state && this->search_complete == false)
	{
		this->search_complete = true;
		this->back_state = final_state;
		std::cout << "found\n";
	}

	if (search_complete)
	{
		if (this->back_state != this->initial_state)
		{
			this->get_box(this->back_state)->type = 3;
			this->get_box(this->back_state)->animating = true;
			this->back_state = this->parents[this->back_state.x][this->back_state.y];
			this->get_box(this->back_state)->animating = true;
		}
		else
		{

			this->app->appState->startSearch = 0;
		}
	}

	if (search_complete == false && queue.empty())
	{
		std::cout << "initializing............\n";
		queue.push(this->initial_state);
		for (int x = 0; x < this->boxOrder; x++)
		{
			for (int y = 0; y < this->boxOrder; y++)
			{
				if (box[x][y]->type == -1)
				{
					this->maze.push_back({x, y});
				}
			}
		}
		return;
	}

	if (search_complete == false)
	{
		std::cout << "solving............\n";
		auto &curr = queue.front();
		for (int i = 0; i < maze.size(); i++)
		{
			if (curr == this->maze[i])
			{
				queue.pop();
				return;
			}
		}
		this->get_box(curr)->animating = true;
		if (curr.x > 0)
		{
			if (!this->visited[curr.x - 1][curr.y])
			{
				queue.push({curr.x - 1, curr.y});
				this->parents[curr.x - 1][curr.y] = curr;
				this->visited[curr.x - 1][curr.y] = true;
			}
		}
		if (curr.x < 39)
		{
			if (!this->visited[curr.x + 1][curr.y])
			{
				queue.push({curr.x + 1, curr.y});
				this->parents[curr.x + 1][curr.y] = curr;
				this->visited[curr.x + 1][curr.y] = true;
			}
		}
		if (curr.y > 0)
		{
			if (!this->visited[curr.x][curr.y - 1])
			{
				queue.push({curr.x, curr.y - 1});
				this->parents[curr.x][curr.y - 1] = curr;
				this->visited[curr.x][curr.y - 1] = true;
			}
		}
		if (curr.y < 39)
		{
			if (!this->visited[curr.x][curr.y + 1])
			{
				queue.push({curr.x, curr.y + 1});
				this->parents[curr.x][curr.y + 1] = curr;
				this->visited[curr.x][curr.y + 1] = true;
			}
		}

		queue.pop();
	}
}

void Search::reset()
{

	init_boxes();
	init_solve();
}

Search::~Search()
{

	for (auto &rows : this->box)
	{
		for (const auto &item : rows)
		{
			delete item;
		}
	}
}
