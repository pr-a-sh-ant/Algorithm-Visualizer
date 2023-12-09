#include "Search.h"
#include <SFML/Graphics.hpp>
#include "State.h"
#include "App.h"

/*
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
	sf::RectangleShape sample_rect(sf::Vector2f(matrix_width, matrix_height));
	sample_rect.setOutlineThickness(2);
	sample_rect.setOutlineColor(sf::Color::White);
	sample_rect.setFillColor(sf::Color::Green);

	box.clear();
	for (int x = 0; x < this->boxOrder; x++)
	{
		std::vector<Box *> temp_box;
		for (int y = 0; y < this->boxOrder; y++)
		{
			sample_rect.setPosition(origin.x + (x * matrix_width), origin.y + (y * matrix_height));
			temp_box.push_back(new Box(origin.x + (x * matrix_width), origin.y + (y * matrix_height), sample_rect, matrix_width, matrix_height, 0));
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
	this->buttons.push_back(new Button(1450, 450, "Algo 1", 200, 80, "setClear"));
	this->buttons.push_back(new Button(1450, 550, "Algo 2", 200, 80, "setClear"));
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
					std::cout << "Set MazeBox As Maze " << std::endl;
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
		std::cout << "\n My Initial State     " << currentNode->state.x << " " << currentNode->state.y << std::endl;
		std::cout << "\n My Final State     " << final_state.x << " " << final_state.y << std::endl;
		
	}

	if (search_complete && back_propagating)
	{
		std::cout << "current out " << this->currentNode->state.x <<" "<<this->currentNode->state.y << std::endl;
		std::cout << this->initial_state.x <<" "<< this->initial_state.y << std::endl;

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
		std::cout << "CURRENT NODE " <<node->state.x<<" "<<node->state.y <<std::endl;
		

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

				std::cout << "\nCHILD     " << child->state.x << " " << child->state.y << std::endl;
				std::cout << "PARENT    " << child->parent->state.x << " " << child->parent->state.y << std::endl;

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

void Search::handle_user_input(sf::Event& event)
{
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
}*/

viz::search::Search::Search(SearchSpace* search_space, const float step_delay)
	: search_space_(search_space), step_delay_(step_delay), step_clock_(0.0f), searching_(false), back_tracking_(false),
	  back_track_box_(sf::Vector2i(-1, -1))
{
}


void viz::search::Search::start_search()
{
	this->searching_ = true;
	this->back_track_box_ = sf::Vector2i(-1, -1);
	this->back_tracking_ = false;
}

void viz::search::Search::run_back_track_step()
{
	if (this->back_track_box_ == sf::Vector2i(-1, -1))
	{
		this->back_track_box_ = this->search_space_->get_goal_box();
	}
	try
	{
		this->back_track_box_ = this->search_space_->get_parent(this->back_track_box_);
	}
	catch (const std::runtime_error&)
	{
		this->back_tracking_ = false;
		return;
	}
	if (this->back_track_box_ == this->search_space_->get_start_box())
	{
		this->back_tracking_ = false;
		return;
	}

	this->search_space_->set_as_path(this->back_track_box_);
}

void viz::search::Search::set_step_delay(const float step_delay)
{
	this->step_delay_ = step_delay;
}

float viz::search::Search::get_step_delay() const
{
	return this->step_delay_;
}

void viz::search::Search::reset()
{
	this->step_clock_ = 0.0f;
	this->search_space_->reset();
	this->searching_ = false;
	this->back_tracking_ = false;
	this->back_track_box_ = sf::Vector2i(-1, -1);
}

void viz::search::Search::update(const float& delta_time_seconds)
{
	auto& global_state = State::get_state_instance();
	global_state.search.visualizer_mode = this->back_tracking_
		                                      ? search_visualizer_mode::backtracking
		                                      : this->searching_
		                                      ? search_visualizer_mode::searching
		                                      : search_visualizer_mode::none;

	this->step_clock_ += delta_time_seconds;
	if (this->step_clock_ < this->step_delay_)
	{
		return;
	}
	step_clock_ -= this->step_delay_;

	if (this->back_tracking_)
	{
		this->run_back_track_step();
	}
	else if (this->searching_)
	{
		try
		{
			this->run_search_step();
		}
		catch (const std::runtime_error&)
		{
			this->searching_ = false;
			this->back_tracking_ = false;

			// TODO: Handle not found
		}
	}
}

bool viz::search::Search::is_searching() const
{
	return this->searching_;
}

viz::search::BreadthFirstSearch::BreadthFirstSearch(SearchSpace* search_space, const float step_delay)
	: Search(search_space, step_delay)
{
	this->queue_ = std::queue<sf::Vector2i>();
}

void viz::search::BreadthFirstSearch::run_search_step()
{
	// If the search is running but the queue is empty, raise exception
	if (this->queue_.empty())
	{
		throw std::runtime_error("Not found");
	}

	const auto current_box_index = this->queue_.front(); // Get the current box index
	this->queue_.pop(); // Pop the current box index from the queue

	// if the current box is the goal box, stop the search
	if (current_box_index == this->search_space_->get_goal_box())
	{
		this->searching_ = false;
		this->back_tracking_ = true;
		return;
	}

	// Push the valid actions of the current box to the queue
	for (const auto& action : this->search_space_->get_valid_actions(current_box_index))
	{
		this->queue_.push(action);
		this->search_space_->set_parent(current_box_index, action);
		this->search_space_->set_as_visited(action);
	}

	if (current_box_index == this->search_space_->get_start_box())
	{
		return;
	}
	this->search_space_->set_as_explored(current_box_index); // Set the current box as explored
}

void viz::search::BreadthFirstSearch::start_search()
{
	if (viz::State::get_state_instance().search.visualizer_mode != search_visualizer_mode::none)
	{
		return;
	}
	Search::start_search();

	this->queue_ = std::queue<sf::Vector2i>(); // Reset the queue

	// Sets the start box as visited and adds it to the queue
	this->search_space_->set_as_visited(this->search_space_->get_start_box());
	this->queue_.push(this->search_space_->get_start_box());
}

viz::search::DepthFirstSearch::DepthFirstSearch(viz::search::SearchSpace* search_space, const float step_delay)
	: Search(search_space, step_delay)
{
	this->stack_ = std::stack<sf::Vector2i>();
}

void viz::search::DepthFirstSearch::run_search_step()
{
	// If the search is running but the stack is empty, raise exception
	if (this->stack_.empty())
	{
		throw std::runtime_error("Not found");
	}

	const auto current_box_index = this->stack_.top(); // Get the current box index
	this->stack_.pop(); // Pop the current box index from the queue

	// if the current box is the goal box, stop the search
	if (current_box_index == this->search_space_->get_goal_box())
	{
		this->searching_ = false;
		this->back_tracking_ = true;
		return;
	}

	// Push the valid actions of the current box to the queue
	for (const auto& action : this->search_space_->get_valid_actions(current_box_index))
	{
		this->stack_.push(action);
		this->search_space_->set_parent(current_box_index, action);
		this->search_space_->set_as_visited(action);
	}

	if (current_box_index == this->search_space_->get_start_box())
	{
		return;
	}
	this->search_space_->set_as_explored(current_box_index); // Set the current box as explored
}

void viz::search::DepthFirstSearch::start_search()
{
	if (viz::State::get_state_instance().search.visualizer_mode != search_visualizer_mode::none)
	{
		return;
	}
	Search::start_search();

	this->stack_ = std::stack<sf::Vector2i>(); // Reset the stack

	// Sets the start box as visited and adds it to the stack
	this->search_space_->set_as_visited(this->search_space_->get_start_box());
	this->stack_.push(this->search_space_->get_start_box());
}




viz::search::AStarSearch::AStarSearch(viz::search::SearchSpace* search_space, const float step_delay)
	: Search(search_space, step_delay)
{
	this->stack_ = std::stack<sf::Vector2i>();
}

void viz::search::AStarSearch::run_search_step()
{
	// If the search is running but the stack is empty, raise exception
	if (this->stack_.empty())
	{
		throw std::runtime_error("Not found");
	}

}

void viz::search::AStarSearch::start_search()
{
	if (viz::State::get_state_instance().search.visualizer_mode != search_visualizer_mode::none)
	{
		return;
	}
	Search::start_search();

	this->stack_ = std::stack<sf::Vector2i>(); // Reset the stack

	// Sets the start box as visited and adds it to the stack
	this->search_space_->set_as_visited(this->search_space_->get_start_box());
	this->stack_.push(this->search_space_->get_start_box());
}
