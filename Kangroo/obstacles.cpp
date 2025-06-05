#include "obstacles.h"
#include <iostream>


    

void obstacles::initialize(const std::string& filepath, sf::Vector2f position, float scale)
{
    speed = 150.f;
    if (Texture.loadFromFile(filepath)) {
        std::cout << "loaded " << filepath << std::endl;
    }
    else {
        std::cout << "Failed to load " << filepath << std::endl;
    }

    Texture.setSmooth(true);
    Sprite.setTexture(Texture);
    Sprite.setPosition(position);
    Sprite.setScale(scale, scale);
}

void obstacles::load()
{

}

void obstacles::update(float deltaTime)
{
    Sprite.move(-speed * deltaTime, 0.f);
    if (Sprite.getPosition().x + Sprite.getGlobalBounds().width < 0) {
        Sprite.setPosition(800.f, 350.f);
    }
}

void obstacles::Draw(sf::RenderWindow& window)
{
    window.draw(Sprite);
}
