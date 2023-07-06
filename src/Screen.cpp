#include "Screen.h"

Screen::Screen(App *app)
{
        this->app = app;
		this->init_box();
}

void Screen::init_box()
{
	for (int x = 0; x < 40; x++)
	{
		std::vector<Entity*> temp_box;
		for (int y = 0; y < 40; y++)
		{
			temp_box.push_back(new Entity(0 + (x * 32), 0 + (y * 32), 32, 32));
		}
		box.push_back(temp_box);
	}
}


void Screen::update(){
	for (int x = 0; x < 40; x++)
	{
		for (int y = 0; y < 40; y++)
		{
			if (*box[x][y] == this->app->mouse)
			{
				box[x][y]->rect.setFillColor(sf::Color::Red);
			}
		}
	}

}

void Screen::render(){

	for (int x = 0; x < 40; x++)
	{
		for (int y = 0; y < 40; y++)
		{
			
			this->app->window->draw(box[x][y]->rect);

		}
	}


}