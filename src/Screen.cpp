#include "Screen.h"

viz::Screen::Screen(App *app)
{
        this->app = app;
		this->init_box();
}

void viz::Screen::init_box()
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


void viz::Screen::update(){
	for (int x = 0; x < 40; x++)
	{
		for (int y = 0; y < 40; y++)
		{
			if (box[x][y]->collides_with(this->app->mouse))
			{
				box[x][y]->mouse_over = true;
				if(this->app->mouse->clicked){
					box[x][y]->clicked=true;
				}
				else{

				box[x][y]->clicked=false;
				}
			}
			else{
				box[x][y]->mouse_over=false;
			}
		
		 box[x][y]->update();
		
		}
	}
}

void viz::Screen::render(){

	for (int x = 0; x < 40; x++)
	{
		for (int y = 0; y < 40; y++)
		{
			this->app->window->draw(box[x][y]->rect);
		}
	}
}
