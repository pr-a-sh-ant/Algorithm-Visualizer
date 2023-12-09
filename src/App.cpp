#include "State.h"
#include "App.h"

/*
App::App()
{
	init_window();
	// std::cout << "window inited............." << std::endl;
	init_variables();
	// std::cout << "APP INIT DONE......" << std::endl;
}

void App::init_window()
{
	sf::VideoMode mode = sf::VideoMode::getDesktopMode();
	this->window = new sf::RenderWindow(mode, "SFML works!", sf::Style::Fullscreen);
	this->mouse = new Mouse();
	init_search();
	init_home();
	init_sort();

}

void App::init_variables()
{
	this->appState = new state;
	this->appState->screen = 0;
	this->appState->startSearch = 0;
	this->appState->resetScreen = 1;
	this->appState->mode = 3;
	// std::cout << "numeric variables inited............." << std::endl;
	deltime = 0.0f;
	if (!font.loadFromFile("Public/font.ttf"))
	{
		std::cout << "Error loading font" << std::endl;
		return;
	}

}

void App::init_search()
{
	this->search = new Search(this);
}

void App::init_home()
{

	this->home = new Home(this);
}

void App::init_sort()
{
	this->sort = new Sort(this);

}

void App::draw()
{
	// std::cout << "drawing............." << std::endl;

	this->window->clear();
	if (appState->screen == 0)
	{
		// std::cout << "drawing home............." << std::endl;
		this->home->draw();
	}
	else if (appState->screen == 1)
	{
		this->search->draw();
	}
	else if (appState->screen == 2)
	{
		this->sort->draw();
	}
	else if (appState->screen == 1)
	{

		this->search->draw();
	}
	this->window->display();
}

void App::update()
{
	// std::cout << "updating............." << std::endl;
	updateSFMLevents();
	if (appState->screen == 0)
	{
		// std::cout << "updating Home............." << std::endl;
		this->home->update();
		if(this->appState->resetScreen){
			this->search->reset();
			this->sort->init();
			this->appState->resetScreen=0;
		}
	}
	else if (appState->screen == 1)
	{
		this->search->update();
	}
	else if (appState->screen == 2)
	{
		// std::cout << "updating sort............." << std::endl;
		this->sort->update();
	}
	else if (appState->screen == -1)
	{
		this->window->clear();
		this->window->close();
	}



	mouse->update(*this->window);
}

void App::updateSFMLevents()
{
	deltime = clock.restart().asSeconds();
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
			this->window->close();
		if (sfEvent.type == sf::Event::KeyPressed)
		{
			if (sfEvent.key.code == sf::Keyboard::Q || sfEvent.key.code == sf::Keyboard::Escape)
			{
				this->window->close();
			}
			else if (sfEvent.key.code == sf::Keyboard::S)
			{
				this->appState->screen = 1;
			}
		}
		else if (sfEvent.type == sf::Event::MouseButtonPressed)
		{
			this->mouse->clicked = true;
		}
		else if (sfEvent.type == sf::Event::MouseButtonReleased)
		{
			this->mouse->clicked = false;
		}
	}
}

void App::run()
{
	while (this->window->isOpen())
	{
		// std::cout << "running............." << std::endl;
		this->update();

		this->draw();
	}
}

App::~App()
{
	delete this->mouse;
}
*/

#pragma region callback functions
void search_callback(viz::App &app)
{
	app.selected_window->reset();
	app.selected_window = app.search_window;
}

void sort_callback(viz::App &app)
{
	app.selected_window->reset();
	app.selected_window = app.sort_window;
}

void back_callback(viz::App &app)
{
	app.selected_window->reset();
	app.selected_window = app.home_window;
}

void exit_callback(viz::App &app)
{
	app.window->close();
}
#pragma endregion

viz::App::App()
	: delta_time_seconds(0.0f)
{
	// Initialize the sfml window
	this->window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Algorithm Visualizer");
	// Initialize the search window
	this->search_window = new viz::window::SearchWindow({1920, 1080}, "Search", [this]()
														{ back_callback(*this); });
	// Initialize the home window
	this->home_window = new viz::window::HomeWindow(
		{1920, 1080}, "Home", [this]()
		{ search_callback(*this); },
		[this]()
		{ sort_callback(*this); },
		[this]()
		{ exit_callback(*this); });
	viz::State::get_state_instance();
	// Initialize the sort window
	this->sort_window = new viz::window::SortWindow({ 1920, 1080 }, "Sort", [this]() {back_callback(*this); });
	// Set the default window
	this->selected_window = this->home_window;

	this->clock.restart();
}

viz::App::~App()
{
	delete this->window;
	delete this->search_window;
}

void viz::App::draw()
{
	this->window->clear();
	this->selected_window->draw(std::ref(*this->window));
	this->window->display();
}

void viz::App::update()
{
	this->delta_time_seconds = this->clock.restart().asSeconds();
	this->selected_window->update(this->delta_time_seconds);
}

void viz::App::handle_state()
{
	viz::State::get_state_instance().mouse.is_left_button_pressed = false;

	while (this->window->pollEvent(this->sf_event))
	{
		switch (this->sf_event.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->sf_event.key.code == sf::Keyboard::Escape)
			{
				this->window->close();
			}
			break;
		case (sf::Event::MouseButtonPressed):
			if (this->sf_event.mouseButton.button == sf::Mouse::Left)
			{
				viz::State::get_state_instance().mouse.is_left_button_down = true;
				viz::State::get_state_instance().mouse.is_left_button_pressed = true;
			}
			break;
		case (sf::Event::MouseButtonReleased):
			if (this->sf_event.mouseButton.button == sf::Mouse::Left)
			{
				viz::State::get_state_instance().mouse.is_left_button_down = false;
			}
			break;
		case sf::Event::MouseMoved:
			viz::State::get_state_instance().update_mouse({this->sf_event.mouseMove.x, this->sf_event.mouseMove.y});
		default:
			break;
		}
	}
	// viz::State::get_state_instance().update_mouse(sf::Mouse::getPosition(std::ref(*this->window)));	// Update the mouse position
	this->selected_window->handle_state_change(viz::State::get_state_instance());
}

#include <iostream>

void viz::App::run()
{
	while (this->window->isOpen())
	{
		this->handle_state();
		this->update();
		this->draw();
	}
}
