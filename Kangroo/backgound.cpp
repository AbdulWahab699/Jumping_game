#include "backgound.h"
#include <iostream>

void backgound::initialize() {
    switchTime = 10.f;
    currentFrame = 0;
    totalFrames = 3;
    if (!Texture.loadFromFile("obstacles-1/backgroundmix.png")) {
        std::cout << "Character failed to Load!" << std::endl;
    }
    else {
        std::cout << "background Loaded!" << std::endl;
    }
    Sprite.setTexture(Texture);
}
void backgound::update() {
    if (clockAnimation.getElapsedTime().asSeconds() >= switchTime) {
        currentFrame++;
        if (currentFrame >= totalFrames) {
            currentFrame = 0;
        }

        Sprite.setTextureRect(sf::IntRect(800 * currentFrame, 0 , 800, 480));
        clockAnimation.restart();
    }
}

void backgound::Draw(sf::RenderWindow& window) {
    window.draw(Sprite);
}
