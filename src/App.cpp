#include "App.h"

#include <iostream>

#include "State.h"
#include "ThreadPool.h"

#pragma region callback functions
void search_callback(viz::App& app)
{
	if (app.search_window == nullptr)
	{
		return;
	}

	app.selected_window->reset();
	app.selected_window = app.search_window;
}

void sort_callback(viz::App& app)
{
	if (app.sort_window == nullptr)
	{
		return;
	}

	app.selected_window->reset();
	app.selected_window = app.sort_window;
}

void back_callback(viz::App& app)
{
	if (app.home_window == nullptr)
	{
		return;
	}

	app.selected_window->reset();
	app.selected_window = app.home_window;
}

void exit_callback(viz::App& app)
{
	app.window->close();
}
#pragma endregion

viz::App::App()
	: selected_window(nullptr), search_window(nullptr), home_window(nullptr), sort_window(nullptr),
	  delta_time_seconds(0.0f)
{
	// Initialize the sfml window
	this->window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Algorithm Visualizer", sf::Style::Fullscreen);

	// Initialize the state
	State::get_state_instance();

	/*
	// Initialize the thread pool
	auto& thread_pool = thread::ThreadPool::initialize();

	// Initialize the home window
	thread_pool.queue_job([this]()
	{
		this->home_window = new window::HomeWindow(
			{1920, 1080}, "Home", [this]()
			{
				search_callback(*this);
			},
			[this]()
			{
				sort_callback(*this);
			},
			[this]()
			{
				exit_callback(*this);
			});
	});
	// Initialize the search window
	thread_pool.queue_job([this]()
	{
		this->search_window = new window::SearchWindow({1920, 1080}, "Search", [this]()
		{
			back_callback(*this);
		});
	});
	// Initialize the sort window
	thread_pool.queue_job([this]()
	{
		this->sort_window = new window::SortWindow({1920, 1080}, "Sort", [this]() { back_callback(*this); });
	});

	// while loop to wait for all the windows to be initialized
	while (this->home_window == nullptr)
	{
		// Waiting for the home window to be initialized
	}*/

	this->home_window = new window::HomeWindow(
		{ 1920, 1080 }, "Home", [this]()
		{
			search_callback(*this);
		},
		[this]()
		{
			sort_callback(*this);
		},
		[this]()
		{
			exit_callback(*this);
		});
	this->search_window = new window::SearchWindow({ 1920, 1080 }, "Search", [this]()
		{
			back_callback(*this);
		});
	this->sort_window = new window::SortWindow({ 1920, 1080 }, "Sort", [this]() { back_callback(*this); });

	this->selected_window = this->home_window;

	this->clock.restart();
}

viz::App::~App()
{
	delete this->window;
	delete this->search_window;
	delete this->home_window;
	delete this->sort_window;

	if (viz::State::is_initialized())
	{
		viz::State::destroy_state_instance();
	}
	if (viz::thread::ThreadPool::is_initialized())
	{
		auto& thread_pool = viz::thread::ThreadPool::get_instance();
		while (thread_pool.busy())
		{
			// Waiting for the thread pool to be free
		}
		thread_pool.stop();
	}
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
	State::get_state_instance().mouse.is_left_button_pressed = false;

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
				State::get_state_instance().mouse.is_left_button_down = true;
				State::get_state_instance().mouse.is_left_button_pressed = true;
			}
			break;
		case (sf::Event::MouseButtonReleased):
			if (this->sf_event.mouseButton.button == sf::Mouse::Left)
			{
				State::get_state_instance().mouse.is_left_button_down = false;
			}
			break;
		case sf::Event::MouseMoved:
			State::get_state_instance().update_mouse({this->sf_event.mouseMove.x, this->sf_event.mouseMove.y});
		default:
			break;
		}
	}
	if (this->selected_window == nullptr)
	{
		throw std::runtime_error("Selected window is null");
	}
	this->selected_window->handle_state_change(State::get_state_instance());
}

void viz::App::run()
{
	while (this->window->isOpen())
	{
		this->handle_state();
		this->update();
		this->draw();
	}
}
