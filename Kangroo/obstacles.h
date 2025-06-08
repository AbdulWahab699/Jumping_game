#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class obstacles {
public:
    void initialize(std::shared_ptr<sf::Texture> texture, sf::Vector2f position, float scale = 0.5f);
    void update(float deltaTime);
    void Draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;


private:
    std::shared_ptr<sf::Texture> Texture;
    sf::Sprite Sprite;
    float speed;
};
