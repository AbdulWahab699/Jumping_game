#include "obstacles.h"
#include <iostream>

void obstacles::initialize(std::shared_ptr<sf::Texture> texture, sf::Vector2f position, float scale) {
    speed = 150.f;
    Texture = texture;
    Sprite.setTexture(*Texture);
    Sprite.setPosition(position);
    Sprite.setScale(scale, scale);
}

void obstacles::update(float deltaTime) {
    Sprite.move(-speed * deltaTime, 0.f);
}

void obstacles::Draw(sf::RenderWindow& window) {
    window.draw(Sprite);
}

sf::FloatRect obstacles::getBounds() const
{
    return Sprite.getGlobalBounds();
}
