#include "SortWindow.h"

#include <iostream>

#include "State.h"

#pragma region button callback functions
namespace sort_callbacks
{
	void back(viz::window::SortWindow& sort_window)
	{
		sort_window.back_callback();
	}

	void change_array_size(const int new_size, viz::window::SortWindow& sort_window)
	{
		auto& state = viz::State::get_state_instance().get_state_instance();
		if (state.sort.visualizer_mode == viz::sort_visualizer_mode::sorting || sort_window.sort_space->number_of_boxes
			== new_size)
		{
			return;
		}
		sort_window.sort_space->set_number_of_boxes(new_size);
	}

	void start_sort(viz::window::SortWindow& sort_window)
	{
		auto& state = viz::State::get_state_instance().get_state_instance();
		if (state.sort.visualizer_mode == viz::sort_visualizer_mode::sorting)
		{
			return;
		}
		if (state.sort.visualizer_mode == viz::sort_visualizer_mode::completed)
		{
			// Reset the sort space
			sort_window.selected_sort_algorithm->reset();
		}
		state.sort.visualizer_mode = viz::sort_visualizer_mode::sorting;
		sort_window.selected_sort_algorithm->start_sort();
	}

	void bubble_sort(viz::window::SortWindow& sort_window)
	{
		auto& state = viz::State::get_state_instance().get_state_instance();
		if (state.sort.visualizer_mode == viz::sort_visualizer_mode::sorting)
		{
			return;
		}
		sort_window.selected_sort_algorithm = sort_window.sort_algorithms["BubbleSort"];
		// Reset the sort space
		sort_window.selected_sort_algorithm->reset();
		state.sort.visualizer_mode = viz::sort_visualizer_mode::none;
	}

	void selection_sort(viz::window::SortWindow& sort_window)
	{
		auto& state = viz::State::get_state_instance().get_state_instance();
		if (state.sort.visualizer_mode == viz::sort_visualizer_mode::sorting)
		{
			return;
		}
		sort_window.selected_sort_algorithm = sort_window.sort_algorithms["SelectionSort"];
		// Reset the sort space
		sort_window.selected_sort_algorithm->reset();
		state.sort.visualizer_mode = viz::sort_visualizer_mode::none;
	}

	void merge_sort(viz::window::SortWindow& sort_window)
	{
		auto& state = viz::State::get_state_instance().get_state_instance();
		if (state.sort.visualizer_mode == viz::sort_visualizer_mode::sorting)
		{
			return;
		}
		sort_window.selected_sort_algorithm = sort_window.sort_algorithms["MergeSort"];
		// Reset the sort space
		sort_window.selected_sort_algorithm->reset();
		state.sort.visualizer_mode = viz::sort_visualizer_mode::none;
	}

	void quick_sort(viz::window::SortWindow& sort_window)
	{
		auto& state = viz::State::get_state_instance().get_state_instance();
		if (state.sort.visualizer_mode == viz::sort_visualizer_mode::sorting)
		{
			return;
		}
		sort_window.selected_sort_algorithm = sort_window.sort_algorithms["QuickSort"];
		// Reset the sort space
		sort_window.selected_sort_algorithm->reset();
		state.sort.visualizer_mode = viz::sort_visualizer_mode::none;
	}

	void radix_sort(viz::window::SortWindow& sort_window)
	{
		auto& state = viz::State::get_state_instance().get_state_instance();
		if (state.sort.visualizer_mode == viz::sort_visualizer_mode::sorting)
		{
			return;
		}
		sort_window.selected_sort_algorithm = sort_window.sort_algorithms["RadixSort"];
		// Reset the sort space
		sort_window.selected_sort_algorithm->reset();
		state.sort.visualizer_mode = viz::sort_visualizer_mode::none;
	}

	void bogo_sort(viz::window::SortWindow& sort_window)
	{
		auto& state = viz::State::get_state_instance().get_state_instance();
		if (state.sort.visualizer_mode == viz::sort_visualizer_mode::sorting)
		{
			return;
		}
		sort_window.selected_sort_algorithm = sort_window.sort_algorithms["BogoSort"];
		// Reset the sort space
		sort_window.selected_sort_algorithm->reset();
		state.sort.visualizer_mode = viz::sort_visualizer_mode::none;
	}

	void reset(viz::window::SortWindow& sort_window)
	{
		sort_window.selected_sort_algorithm->reset();
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
	void (*callback)(viz::window::SortWindow& sort_window);
};

void viz::window::SortWindow::init_buttons()
{
	const std::vector<ButtonInfo> button_infos = {
		{{1350, 900}, {200, 80}, "Back", {204, 0, 0}, {255, 0, 0}, sort_callbacks::back}, // Back Button
		{{1300, 50}, {250, 80}, "Start", {58, 107, 102}, {116, 216, 143}, sort_callbacks::start_sort}, // Start Button
		{{1600, 50}, {250, 80}, "Reset", {9, 57, 120}, {19, 98, 168}, sort_callbacks::reset}, // Reset
		{{1300, 250}, {250, 80}, "Bubble", {9, 57, 120}, {19, 98, 168}, sort_callbacks::bubble_sort}, // Bubble sort
		{{1300, 350}, {250, 80}, "Selection", {9, 57, 120}, {19, 98, 168}, sort_callbacks::selection_sort},
		// Selection Sort
		{{1300, 450}, {250, 80}, "Quick", {9, 57, 120}, {19, 98, 168}, sort_callbacks::quick_sort}, // Quick sort
		{{1300, 550}, {250, 80}, "Merge", {9, 57, 120}, {19, 98, 168}, sort_callbacks::merge_sort}, // Merge Sort
		{{1300, 650}, {250, 80}, "Radix", {9, 57, 120}, {19, 98, 168}, sort_callbacks::radix_sort}, // Merge Sort
		{{1300, 750}, {250, 80}, "Bogo", {9, 57, 120}, {19, 98, 168}, sort_callbacks::bogo_sort}, // Merge Sort
		// Size changing Buttons
		{
			{1600, 250}, {250, 80}, "Size:50", {9, 57, 120}, {19, 98, 168}, [](SortWindow& sort_window)
			{
				sort_callbacks::change_array_size(50, sort_window);
			}
		},
		{
			{1600, 350}, {250, 80}, "Size:100", {9, 57, 120}, {19, 98, 168}, [](SortWindow& sort_window)
			{
				sort_callbacks::change_array_size(100, sort_window);
			}
		},
		{
			{1600, 450}, {250, 80}, "Size:200", {9, 57, 120}, {19, 98, 168}, [](SortWindow& sort_window)
			{
				sort_callbacks::change_array_size(200, sort_window);
			}
		},
		{
			{1600, 550}, {250, 80}, "Size:500", {9, 57, 120}, {19, 98, 168}, [](SortWindow& sort_window)
			{
				sort_callbacks::change_array_size(500, sort_window);
			}
		},
		{
			{1600, 650}, {250, 80}, "Size:1000", {9, 57, 120}, {19, 98, 168}, [](SortWindow& sort_window)
			{
				sort_callbacks::change_array_size(1000, sort_window);
			}
		}
	};

	for (const auto& button_info : button_infos)
	{
		auto button = new Button(button_info.position, button_info.dimensions, button_info.text, "Public/font.ttf",
		                         button_info.fill_color, button_info.fill_color_hover, [this, button_info]()
		                         {
			                         button_info.callback(*this);
		                         });
		this->buttons_.push_back(button);
	}
}

void viz::window::SortWindow::handle_state_change_button(State& state)
{
	for (const auto& button : this->buttons_)
	{
		button->handle_mouse(state.mouse);
	}
}

void viz::window::SortWindow::update_button(const float delta_time_seconds)
{
	for (const auto& button : this->buttons_)
	{
		button->update();
	}
}

void viz::window::SortWindow::draw_button(sf::RenderWindow& window)
{
	for (const auto& button : this->buttons_)
	{
		button->draw(window);
	}
}

viz::window::SortWindow::SortWindow(const sf::Vector2u& window_size, const std::string& title,
                                    std::function<void()> back_callback)
	: Window(window_size, title), back_callback(std::move(back_callback))
{
	bar_width = bounding_rect_width / number_of_bars;

	this->sort_space = new sort::SortSpace(sort_space_start_position, bar_min_height, bar_max_height, bar_width,
	                                       number_of_bars, bars_offset);

	// Initialize the sort algorithms
	this->sort_algorithms["BubbleSort"] = new sort::BubbleSort(sort_space, step_delay); // Bubble sort
	this->sort_algorithms["SelectionSort"] = new sort::SelectionSort(sort_space, step_delay); // Insertion sort
	this->sort_algorithms["MergeSort"] = new sort::MergeSort(sort_space, step_delay); // Merge sort
	this->sort_algorithms["QuickSort"] = new sort::QuickSort(sort_space, step_delay); // Quick sort
	this->sort_algorithms["RadixSort"] = new sort::RadixSort(sort_space, step_delay); // Radix sort
	this->sort_algorithms["BogoSort"] = new sort::BogoSort(sort_space, step_delay); // Bogo sort

	this->selected_sort_algorithm = sort_algorithms["BubbleSort"];

	// Initialize button
	this->init_buttons();
	this->sort_text = sf::Text("Sort Algorithm", this->buttons_[0]->font, 60);
	sort_text.setPosition(1350, 150);
}

viz::window::SortWindow::~SortWindow()
{
	delete sort_space;

	// Delete the sort algorithms
	for (auto& [name, algorithm] : sort_algorithms)
	{
		delete algorithm;
	}
}

void viz::window::SortWindow::reset()
{
	this->selected_sort_algorithm->reset();
}

void viz::window::SortWindow::draw(sf::RenderWindow& window)
{
	window.draw(sort_text);
	this->sort_space->draw(window);
	this->draw_button(window);
}

void viz::window::SortWindow::update(const float delta_time_seconds)
{
	this->selected_sort_algorithm->update(delta_time_seconds);
	this->update_button(delta_time_seconds);
}

void viz::window::SortWindow::handle_state_change(State& state)
{
	this->handle_state_change_button(state);
}
