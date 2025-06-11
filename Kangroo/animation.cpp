#include "animation.h"
#include <iostream>


void animation::initialize() {
    if (!Texture.loadFromFile("character.png")) {
        std::cout << "Character failed to Load!" << std::endl;
    }
    else {
        std::cout << "Character Loaded!" << std::endl;
    }
    if (!jumpBuffer.loadFromFile("jump-main.wav")) {
        std::cerr << "Failed load jump.wav" << std::endl;
    }
    
    jumpSound.setBuffer(jumpBuffer);
    Texture.setSmooth(true);
    Sprite.setTexture(Texture);
    Sprite.setPosition(50.f, 300.f);

    // Initialize animation timing
    switchTime = 0.15f;
    jumpSwitchTime = 0.50f;
    currentFrame = 0;
    totalFrames = 6;
    jumpTotal = 2;
}


void animation::update() {
    if (clockAnimation.getElapsedTime().asSeconds() >= switchTime) {
        currentFrame++;
        if (currentFrame >= totalFrames) {
            currentFrame = 0;
        }

        Sprite.setTextureRect(sf::IntRect(85 * currentFrame, 0, 85, 100));
        clockAnimation.restart();
    }
}

void animation::jumpUpdate()
{
    if (clockAnimation.getElapsedTime().asSeconds() >= jumpSwitchTime) {
        currentFrame++;
        if (currentFrame >= jumpTotal) {
            currentFrame = 0;
        }

        Sprite.setTextureRect(sf::IntRect(85 * currentFrame, 150, 85, 120));
        clockAnimation.restart();
    }
}


void animation::Draw(sf::RenderWindow& window) {
    window.draw(Sprite);
}
