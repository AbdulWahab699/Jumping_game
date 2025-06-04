#include "obstacles.h"
#include <iostream>
void obstacles::intitialize()
{
	
}

void obstacles::load()
{
	if (Texture.loadFromFile("obstacles-1/boxAlt.png")) {
		std::cout << "Obstacle is loaded!" << std::endl;
	}
	else {
		std::cout << "Obstacle failed to load!" << std::endl;
	}
	Texture.setSmooth(true);
	Sprite.setTexture(Texture);
	Sprite.setPosition(300.f, 350.f);
	Sprite.setScale(0.7f,0.7f);
}
void obstacles::update()
{


}
void obstacles::Draw(sf::RenderWindow& window)
{
	window.draw(Sprite);
}