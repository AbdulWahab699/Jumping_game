#include "pathway.h"
#include <iostream>

void pathway::initialize() {
    switchTime = 5.f;
    currentFrame = 0;
    totalFrames = 3;
    if (!Texture.loadFromFile("obstacles-1/pathwaymix.png")) {
        std::cout << "Pathway failed to Load!" << std::endl;
    }
    else {
        std::cout << "Pathway Loaded!" << std::endl;
    }
    Sprite.setTexture(Texture);
    Sprite.setPosition(0.f, 400.f);
}
void pathway::update() {
    if (clockAnimation.getElapsedTime().asSeconds() >= switchTime) {
        currentFrame++;
        if (currentFrame >= totalFrames) {
            currentFrame = 0;
        }

        Sprite.setTextureRect(sf::IntRect(800 * currentFrame, 0, 800, 100));
        clockAnimation.restart();
    }
}
void pathway::Draw(sf::RenderWindow& window) {
    window.draw(Sprite);
}
