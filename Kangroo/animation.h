#pragma once
#include <SFML/Graphics.hpp>

class animation {
private:
    sf::Texture Texture;
    sf::Clock clockAnimation;
    float switchTime;
    int currentFrame;
    int totalFrames;
    int jumpTotal;
    float jumpSwitchTime;

public:
    sf::Sprite Sprite;

    void initialize();
    void update();
    void jumpUpdate();
    void Draw(sf::RenderWindow& window);
};
