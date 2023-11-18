#include "App.h"
#include "Search.h"


App::App(){
    init_window();
}


void App::init_window()
{
	sf::VideoMode mode = sf::VideoMode::getDesktopMode();
	this->window = new sf::RenderWindow(mode, "SFML works!");

}

void App::init_variables()
{
	deltime = 0.0f;
}

void App::init_search()
{
    this->search = new Search(this);

}

void App::draw()
{
	this->window->clear();
	
	this->window->display();
}

void App::update()
{

    updateSFMLevents();
	mouse->update(*window);


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
				
			}
		}
	}
}

void App::run()
{
    while (this->window->isOpen())
	{

            this->update();

            this->draw();

    }
}


App::~App()
{
    delete this->mouse;

}