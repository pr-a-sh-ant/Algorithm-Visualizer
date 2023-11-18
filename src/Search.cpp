#include "Search.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Box* Search::get_box(sf::Vector2i& pos)
{
	return this->box[pos.x][pos.y];
}

Search::Search()
{
	init_boxes();
	init_window();
	init_variables();
	init_solve();
	this->mouse = new Mouse(this->box);
}

void Search::init_solve()
{
	sf::Vector2i temp = {-1, -1};

	for (int x = 0; x < 40; x++)
	{
		std::vector<bool> visited_temp;
		std::vector<sf::Vector2i> parents_temp;
		for (int y = 0; y < 40; y++)
		{
			visited_temp.emplace_back(false);
			parents_temp.emplace_back(temp);
		}
		this->parents.emplace_back(parents_temp);
		this->visited.emplace_back(visited_temp);
	}
}

void Search::init_variables()
{
	deltime = 0.0f;
}

void Search::init_boxes()
{
	for (int x = 0; x < 40; x++)
	{
		std::vector<Box*> temp_box;
		for (int y = 0; y < 40; y++)
		{
			temp_box.push_back(new Box(origin.x + (x * 32), origin.y + (y * 32), 32, 32));
		}
		box.push_back(temp_box);
	}
}

void Search::updateSFMLevents()
{
	deltime = clock.restart().asSeconds();
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
			this->window->close();
		if (sfEvent.type == sf::Event::KeyPressed)
		{
			if (sfEvent.key.code == sf::Keyboard::Q or sfEvent.key.code == sf::Keyboard::Escape)
			{
				this->window->close();
			}
			else if (sfEvent.key.code == sf::Keyboard::S)
			{
				this->searching = true;
			}
		}
	}
}

void Search::update()
{
	updateSFMLevents();
	mouse->update(*window);


	totalTime += deltime;


	if (searching)
	{
		solve();
		totalTime = 0;
	}
	update_boxes();
}

void Search::update_boxes()
{
	for (int x = 0; x < 40; x++)
	{
		for (int y = 0; y < 40; y++)
		{
			if (box[x][y]->animating)
			{
				box[x][y]->animate(deltime);
			}
		}
	}
}

void Search::draw_boxes()
{
	//Draw
	for (int x = 0; x < 40; x++)
	{
		for (int y = 0; y < 40; y++)
		{
			if (!box[x][y]->animating)
				window->draw(box[x][y]->rect);
		}
	}
	for (int x = 0; x < 40; x++)
	{
		for (int y = 0; y < 40; y++)
		{
			if (box[x][y]->animating)
				window->draw(box[x][y]->rect);
		}
	}
}

void Search::draw()
{
	window->clear();
	draw_boxes();
	window->display();
}

void Search::init_window()
{
	sf::VideoMode mode = sf::VideoMode::getDesktopMode();
	this->window = new sf::RenderWindow(mode, "SFML works!");
}

void Search::run()
{
	while (this->window->isOpen())
	{
		// * Update

		update();


		// * Draw

		draw();
	}
}

void Search::solve()
{
	std::cout << "solving\n";
	if (searching && queue.empty())
	{
		queue.push(this->initial_state);
		return;
	}
	if (this->queue.front() == this->final_state)
	{
		sf::Vector2i curr_gg = this->final_state;
		while(curr_gg != this->initial_state)
		{
			this->get_box(curr_gg)->animating = true;
			curr_gg = this->parents[curr_gg.x][curr_gg.y];
		}
		this->get_box(curr_gg)->animating = true;

		this->search_complete = true;
		this->searching = false;
		std::cout << "found\n";
		return;
	}

	auto& curr = queue.front();
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

Search::~Search()
{
	delete this->mouse;

	for (auto& rows : this->box)
	{
		for (const auto& item : rows)
		{
			delete item;
		}
	}
}
