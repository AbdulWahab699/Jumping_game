#pragma once
#include <SFML/Graphics.hpp>
class score
{
public:
	sf::Clock scoreClock;
	float score;
	float scoreAdd;
	void initialize();
	void load();
	void update();
	void Draw(sf::RenderWindow& window);
	sf::Font font;
private:

};

