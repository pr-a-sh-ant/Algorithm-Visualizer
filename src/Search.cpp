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
	init();
	init_boxes();
	init_solve();
}

void Search::init()
{
	if (!backgroundTexture.loadFromFile("src/Public/search.jpg"))
	{
		std::cout << "Error loading Texture" << std::endl;
		return;
	}
	background.setSize((sf::Vector2f(1920, 1080)));
	background.setTexture(&backgroundTexture);
	background.setPosition(sf::Vector2f(0, 0));

	if (!startButton.loadFromFile("src/Public/startSearch.png"))
	{
		std::cout << "Error loading Texture" << std::endl;
		return;
	}
	startsearch.setSize((sf::Vector2f(1920, 1080)));
	startsearch.setTexture(&startButton);
	startsearch.setPosition(sf::Vector2f(0, 0));

	clearSearch.setSize(sf::Vector2f(100, 50));
	clearSearch.setFillColor(sf::Color::Cyan);
	clearSearch.setPosition(1600, 20);

	back.setString("Back");
	back.setFont(app->font);
	back.setCharacterSize(50);
	back.setPosition(sf::Vector2f(1600, 910));
	back.setFillColor(sf::Color::Black);
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

void Search::init_boxes()
{
	for (int x = 0; x < 40; x++)
	{
		std::vector<Box *> temp_box;
		for (int y = 0; y < 40; y++)
		{
			temp_box.push_back(new Box(origin.x + (x * 32), origin.y + (y * 32), 32, 32));
		}
		box.push_back(temp_box);
	}
}

void Search::init_buttons()
{
}

void Search::update()
{
	if (app->sfEvent.type == sf::Event::MouseButtonPressed)
	{
		if (back.getGlobalBounds().contains(sf::Mouse::getPosition(*(app->window)).x, sf::Mouse::getPosition(*(app->window)).y))
		{
			*(app->current) = 0;
		}
	}

	totalTime += this->app->deltime;

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
				box[x][y]->animate(this->app->deltime);
			}
		}
	}
}

void Search::draw_boxes()
{
	// Draw
	for (int x = 0; x < 40; x++)
	{
		for (int y = 0; y < 40; y++)
		{
			if (!box[x][y]->animating)
				app->window->draw(box[x][y]->rect);
		}
	}
	for (int x = 0; x < 40; x++)
	{
		for (int y = 0; y < 40; y++)
		{
			if (box[x][y]->animating)
				app->window->draw(box[x][y]->rect);
		}
	}
}

void Search::draw()
{
	app->window->draw(background);
	draw_boxes();
	app->window->draw(back);
	app->window->draw(startsearch);
	app->window->draw(clearSearch);
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
		while (curr_gg != this->initial_state)
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

	auto &curr = queue.front();
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

	for (auto &rows : this->box)
	{
		for (const auto &item : rows)
		{
			delete item;
		}
	}
}
