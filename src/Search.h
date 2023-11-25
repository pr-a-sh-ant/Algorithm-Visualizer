#pragma once

#include "Node.h"
#include "Button.h"
#include <queue>
#include "App.h"
#include "Box.h"

class Box;
class Button;
class App;

class Search
{
private:
	int matrix_height = 28;
	int matrix_width = 28;
	int boxOrder = 37;
	Box *get_box(sf::Vector2i &pos);

public:
	Search(App *app);
	~Search();
	App *app;
	sf::Vector2i origin = sf::Vector2i(25, 25);
	std::vector<std::vector<Box *>> box;
	std::vector<Button *> buttons;

	float totalTime = .0f;
	float switchTIme = .1f;
	bool searching = false;
	bool search_complete = false;

	// For search
	std::queue<sf::Vector2i> queue;
	std::vector<std::vector<bool>> visited;
	std::vector<std::vector<sf::Vector2i>> parents;
	std::vector<sf::Vector2i> maze;
	sf::Vector2i initial_state = sf::Vector2i(5, 5);
	sf::Vector2i final_state = sf::Vector2i(20, 20);
	sf::Vector2i back_state = final_state;
	sf::Text *textAlgo;

	void init_boxes();
	void init_buttons();
	void init();

	void update();
	void update_boxes();
	void update_buttons();

	void draw_boxes();
	void draw_buttons();
	void draw();

	void solve();
	void init_solve();

	void reset();
};
