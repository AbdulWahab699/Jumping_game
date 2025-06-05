#pragma once
#include <SFML/Graphics.hpp>

class obstacles {
public:
    void initialize(const std::string& texturePath, sf::Vector2f position, float scale = 0.5f);                      // Initialize variables
    void load();                            // Load texture and setup sprite
    void update(float deltaTime);           // Update obstacle position using delta time
    void Draw(sf::RenderWindow& window);    // Draw sprite on the screen

private:
    sf::Texture Texture;                   
    sf::Sprite Sprite;                     
    float speed;  
    
};
