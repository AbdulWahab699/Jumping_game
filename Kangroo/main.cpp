#include <SFML/Graphics.hpp>
#include <iostream>
#include "obstacles.h"
#include "animation.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 480), "Kangaroo Game");
    animation character;
    obstacles obstacles;
    character.initialize();
    obstacles.load();

    sf::Clock clock;
    float gravity = 981.f;
    float jumpForce = -500.f;
    bool isJumping = false;
    float velocityY = 0.f;
    float groundY = 300.f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();

        // Handle jumping
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isJumping) {
            velocityY = jumpForce;
            isJumping = true;
        }

        // Apply gravity
        velocityY += gravity * deltaTime;
        character.Sprite.move(0.f, velocityY * deltaTime);

        // Collision with ground
        if (character.Sprite.getPosition().y >= groundY) {
            character.Sprite.setPosition(character.Sprite.getPosition().x, groundY);
            velocityY = 0.f;
            isJumping = false;
        }
        if (isJumping)
        {
            character.jumpUpdate();
        }
        if (!isJumping)
        {
            character.update();
        }
        window.clear(sf::Color::White);
        character.Draw(window);
        obstacles.Draw(window);
        window.display();
    }

    return 0;
}