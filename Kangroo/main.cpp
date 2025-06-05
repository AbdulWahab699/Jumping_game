#include <SFML/Graphics.hpp>
#include <iostream>
#include "obstacles.h"
#include "animation.h"
#include <vector>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 480), "Kangaroo Game");
    window.setFramerateLimit(60);

    sf::Texture texture;
    if (texture.loadFromFile("obstacles-1/background.png")) {
        std::cout << "Background Loaded!" << std::endl;
    }
    else {
        std::cout << "Background Failed to Load!" << std::endl;
    }
    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(texture);
    sf::Clock deltaClock;

    animation character;
    

    character.initialize();

    std::vector<obstacles> obstacleList(11);
    std::vector<std::string> filepath = {
        "obstacles-1/grass.png",
        "obstacles-1/boxAlt.png",
        "obstacles-1/boxCoin.png",
        "obstacles-1/boxExplosive.png",
        "obstacles-1/fence.png",
        "obstacles-1/dirt.png",
        "obstacles-1/boxWarning.png",
        "obstacles-1/spikes.png",
        "obstacles-1/boxItem_disabled.png",
        "obstacles-1/lock_Green.png",
        "obstacles-1/hill_Large.png"
    };

    for (int i = 0; i < 11; i++) {
        float spacing = 250.f;
        sf::Vector2f position(800.f + i * spacing, 370.f);
        obstacleList[i].initialize(filepath[i], position);
    }

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

       
        float deltaTime = deltaClock.restart().asSeconds();

     
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isJumping) {
            velocityY = jumpForce;
            isJumping = true;
        }

        // ⬇️ Gravity
        velocityY += gravity * deltaTime;
        character.Sprite.move(0.f, velocityY * deltaTime);


        if (character.Sprite.getPosition().y >= groundY) {
            character.Sprite.setPosition(character.Sprite.getPosition().x, groundY);
            velocityY = 0.f;
            isJumping = false;
        }

  
        if (isJumping) {
            character.jumpUpdate();
        }
        else {
            character.update();
        }

        for (auto& ob : obstacleList) {
            ob.update(deltaTime);
        }


       
        window.clear(sf::Color::White);
        window.draw(backgroundSprite);
        character.Draw(window);
        for (auto& ob : obstacleList) {
            ob.Draw(window);
        }
        window.display();
    }

    return 0;
}
