#include <SFML/Graphics.hpp>
class App;
#include "App.h" 

#include "Mouse.h"
#include <iostream>


Mouse::Mouse(App *app){
	this->app = app;
}

void Mouse::init(){
		if(!this->font->loadFromFile("/Fonts/Roborto-Regular.ttf"),50){
		// throw "Font Not Found";
		std::cout<<"FontNotFound"<<std::endl;
        
	}
	this->PosText->setFont(*this->font);
	this->PosText->setCharacterSize(60);
    this->PosText->setFillColor(sf::Color::Black);
    this->PosText->setOrigin(this->PosText->getLocalBounds().width/2. , this->PosText->getLocalBounds().height/2.);
	
	

}


void Mouse::update()
{
	this->pos->x = sf::Mouse::getPosition(*app->window).x;
	this->pos->y = sf::Mouse::getPosition(*app->window).y;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		
		std::cout<<"CLicked"<<std::endl;
	
	}
	this->render();
}

void Mouse::render(){
	this->PosText->setString(std::to_string(this->pos->x));
	this->PosText->setString(std::to_string(this->pos->y));
	
	this->app->window->draw(*this->PosText);


}