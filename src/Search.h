#pragma once
class App;
#include "Node.h"
#include <queue>
#include "App.h"


class Search
{
private:
	int matrix_height = 32;
	int matrix_width = 32;
	Box* get_box(sf::Vector2i& pos);

public:
	Search();
	Search(App *app);
	~Search();

	App *app;
	sf::Vector2i origin = sf::Vector2i(32, 32);
	std::vector<std::vector<Box*>> box;
	
	float totalTime = .0f;
	float switchTIme = .1f;
	bool searching = false;
	bool search_complete = false;

	// For search
	std::queue<sf::Vector2i> queue;
	std::vector<std::vector<bool>> visited;
	std::vector<std::vector<sf::Vector2i>> parents;
	sf::Vector2i initial_state = sf::Vector2i(5, 5);
	sf::Vector2i final_state = sf::Vector2i(20, 20);


	void init_variables();
	void init_window();
	void init_boxes();

	void update();
	void updateSFMLevents();
	void update_boxes();

	void draw_boxes();
	void draw();

	void solve();
	void init_solve();

	void run();
};
