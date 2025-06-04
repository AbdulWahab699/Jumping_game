#include "obstacles.h"
#include <iostream>
void obstacles::intitialize()
{
	
}

void obstacles::load()
{
	if (Texture.loadFromFile("Pillars 1.png")) {
		std::cout << "Obstacle is loaded!" << std::endl;
	}
	else {
		std::cout << "Obstacle failed to load!" << std::endl;
	}
	Texture.setSmooth(true);
	Sprite.setTexture(Texture);
	Sprite.setPosition(300.f, 300.f);
	Sprite.setScale(1.f,1.f);
}
void obstacles::update()
{


}
void obstacles::Draw(sf::RenderWindow& window)
{
	window.draw(Sprite);
}