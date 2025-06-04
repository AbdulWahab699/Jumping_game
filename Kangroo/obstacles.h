#pragma once
#include <SFML/Graphics.hpp>
class obstacles
{
public:
	sf::Texture Texture;
	sf::Sprite Sprite;
public:
	void intitialize();
	void load();
	void update();
	void Draw(sf::RenderWindow& window);
};

