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
	back_state = final_state;
	back_propagating=false;
	
}

void Search::init_boxes()
{	
	box.clear();
	for (int x = 0; x < this->boxOrder; x++)
	{
		std::vector<Box *> temp_box;
		for (int y = 0; y < this->boxOrder; y++)
		{
			Box *bo = new Box(origin.x + (x * matrix_width), origin.y + (y * matrix_height), matrix_width, matrix_height, 0);
			for (int a =0;a<defaultMaze.size();a++){
				if(defaultMaze[a].x ==x && defaultMaze[a].y==y){
					bo->type=-1		;
				}
			}
			temp_box.push_back(bo);
		}
		box.push_back(temp_box);
	}
}

void Search::init_buttons()
{
	this->buttons.push_back(new Button(1400, 980, "Back", 200, 80, "goBack"));
	this->buttons.push_back(new Button(1600, 50, "Maze", 300, 80, "modeMaze"));
	this->buttons.push_back(new Button(1600, 150, "Destination", 300, 80, "modeDestination"));
	this->buttons.push_back(new Button(1200, 150, "Start Point", 300, 80, "modeStart"));
	this->buttons.push_back(new Button(1200, 50, "Search", 300, 80, "setSearching"));
	this->buttons.push_back(new Button(1450, 250, "Clear", 200, 80, "setClear"));
	this->buttons.push_back(new Button(1450, 450, "BFS", 200, 80, "bfs"));
	this->buttons.push_back(new Button(1450, 550, "DFS", 200, 80, "dfs"));
}

void Search::update()
{

	totalTime += this->app->deltime;

	if (this->app->appState->startSearch == 1)
	{
		searching = true;
	}
	if (this->app->appState->clear == 1 )
	{
		reset();
	}

	if (searching && totalTime > switchTIme)
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

	

	if (alg.empty() && this->search_complete == false)
	{
		
		this->back_state = final_state;
		this->alg.type = this->app->appState->searchAlg;
		std::cout << "Alg type " << this->alg.type << std::endl;
		Box::changeSwitchTime(switchTIme);
		

		currentNode = new Node(initial_state,box[initial_state.x][initial_state.y]);

		alg.add(currentNode);	

		
		for (int x = 0; x < boxOrder; x++)
			{
				for (int y = 0; y < boxOrder; y++)
				{
					if(box[x][y]->type==-1){
						this->maze.push_back({x,y});
						
					}
				}

			}
	
		std::cout << "Initialized \n";
		
	}

	if (search_complete && back_propagating)
	{
		

		if (this->currentNode->state != this->initial_state)
		{
			this->currentNode->box->type = 3;
			
			this->currentNode->box->animating = true;			
			this->currentNode = new Node(*this->currentNode->parent);
			Node *parent = this->currentNode->parent;
			
		}
		else
		{
			back_propagating = false;
			this->app->appState->startSearch = 0;
			std::cout << "BACK PROPAGATING......" << std::endl;
			
		}
	}

	

	if ( !search_complete){


		Node *node = alg.remove();
		

		if(node->state == final_state ){
			search_complete = true;
			back_propagating = true;
			
			this->currentNode = node;
			std::cout << "Searching Complete.... " << std::endl;
			return;
			
		}


		node->box->animating = true;

		alg.explored.push_back(node->state);


		std::cout << "\n Explored  " << alg.explored.size() << std::endl;


		std::vector<sf::Vector2i> act = node->get_actions();


		for (int a = 0; a < act.size(); a++)
		{
			if (!alg.contains_state(act[a]) && !alg.inExplored(act[a]))
			{
				Box* box_ = box[act[a].x][act[a].y];


				auto child = new Node(sf::Vector2i(act[a].x, act[a].y), node, sf::Vector2i(act[a].x, act[a].y), box_);

				// std::cout << "\nCHILD     " << child->state.x << " " << child->state.y << std::endl;
				// std::cout << "PARENT    " << child->parent->state.x << " " << child->parent->state.y << std::endl;

				if(child->state.x < boxOrder && child->state.y < boxOrder && !child->in_maze(maze) ){

					alg.add(child);
				}
			}
		}
		std::cout << "Frontier  " << alg.frontier.size() << std::endl;

		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
	}

}

void Search::reset()
{

	init_boxes();
	init_solve();
	alg.reset();
	maze.clear();	
	this->app->appState->clear=0;
	this->app->appState->startSearch=0;
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
