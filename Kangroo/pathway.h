#pragma once
#include <SFML/Graphics.hpp>
class pathway
{
public:
	float switchTime;
	int currentFrame;
	int totalFrames;
	sf::Texture Texture;
	sf::Clock clockAnimation;
	sf::Sprite Sprite;
	void initialize();
	void update();
	void Draw(sf::RenderWindow& window);
};

