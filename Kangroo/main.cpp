#include <SFML/Graphics.hpp>
#include <iostream>
#include "obstacles.h"
#include "animation.h"
#include "score.h"
#include <vector>
#include <memory>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 480), "Not decided yet Game");
    window.setFramerateLimit(60);
    sf::Clock deltaClock;

    //sound


    //score system
    score gameScore;
    gameScore.initialize();
    // Collision detection
    bool showCollisionEffect = false;
    sf::Clock collisionEffectClock;
    float collisionEffectDuration = 0.2f;

    // Background
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("obstacles-1/background.png"))
        std::cout << "Background Failed to Load!" << std::endl;
    sf::Sprite backgroundSprite(backgroundTexture);

    // Pathway
    sf::Texture pathTexture;
    if (!pathTexture.loadFromFile("obstacles-1/pathway.png"))
        std::cout << "Pathway Failed to Load!" << std::endl;
    sf::Sprite pathSprite(pathTexture);
    pathSprite.setPosition(0.f, 400.f);

    // Character
    animation character;
    character.initialize();

    // Load obstacle textures
    std::vector<std::string> filepaths = {
        "obstacles-1/grass.png", "obstacles-1/boxAlt.png", "obstacles-1/boxCoin.png",
        "obstacles-1/boxExplosive.png", "obstacles-1/fence.png", "obstacles-1/dirt.png",
        "obstacles-1/boxWarning.png", "obstacles-1/spikes.png", "obstacles-1/boxItem_disabled.png",
        "obstacles-1/lock_Green.png"
    };

    std::vector<std::shared_ptr<sf::Texture>> textures;
    for (const auto& path : filepaths) {
        auto tex = std::make_shared<sf::Texture>();
        if (tex->loadFromFile(path))
            std::cout << "Loaded: " << path << std::endl;
        else
            std::cout << "Failed to load: " << path << std::endl;
        tex->setSmooth(true);
        textures.push_back(tex);
    }

    std::vector<obstacles> activeObstacles;
    sf::Clock spawnClock;
    float spawnDelay = 2.0f;
    int currentObstacleIndex = 0;

    // Physics
    float gravity = 981.f;
    float jumpForce = -570.f;
    bool isJumping = false;
    float velocityY = 0.f;
    float groundY = 300.f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        };
        float deltaTime = deltaClock.restart().asSeconds();

        // Jump
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isJumping) {
            character.jumpSound.play();
            
            velocityY = jumpForce;
            isJumping = true;
        }

        // Apply gravity
        velocityY += gravity * deltaTime;
        character.Sprite.move(0.f, velocityY * deltaTime);

        // Ground collision
        if (character.Sprite.getPosition().y >= groundY) {
            character.Sprite.setPosition(character.Sprite.getPosition().x, groundY);
            velocityY = 0.f;
            isJumping = false;
        }

        // Animation
        if (isJumping)
            character.jumpUpdate();
        else
            character.update();

        // Spawn obstacle
        if (spawnClock.getElapsedTime().asSeconds() > spawnDelay) {
            obstacles ob;
            ob.initialize(textures[currentObstacleIndex], sf::Vector2f(800.f, 370.f)); // align with kangaroo
            activeObstacles.push_back(ob);
            currentObstacleIndex = (currentObstacleIndex + 1) % textures.size();
            spawnClock.restart();
        }


        // Update and check collisions
        for (auto& ob : activeObstacles) {
            ob.update(deltaTime);

            if (character.Sprite.getGlobalBounds().intersects(ob.getBounds())) {
                    if (!showCollisionEffect) {
                        std::cout << "Collision Detected!" << std::endl;
                        showCollisionEffect = true;
                        collisionEffectClock.restart();
                    }
                
            }
        }

        //Score System
    
        gameScore.update();

        // Draw
        window.clear(sf::Color::White);
        window.draw(backgroundSprite);
        window.draw(pathSprite);
        character.Draw(window);
        gameScore.Draw(window);

        // Draw obstacles
        for (auto& ob : activeObstacles) {
            ob.Draw(window);

            // Debug: obstacle hitbox (blue)
            sf::RectangleShape obstacleBox;
            sf::FloatRect obBounds = ob.getBounds();
            obstacleBox.setSize({ obBounds.width, obBounds.height });
            obstacleBox.setPosition(obBounds.left, obBounds.top);
            obstacleBox.setFillColor(sf::Color::Transparent);
            obstacleBox.setOutlineColor(sf::Color::Transparent);
            obstacleBox.setOutlineThickness(1.f);
            window.draw(obstacleBox);
        }

        // Debug: character hitbox (red)
        sf::FloatRect charBounds = character.Sprite.getGlobalBounds();
        sf::RectangleShape charBox;
        charBox.setSize({ charBounds.width, charBounds.height });
        charBox.setPosition(charBounds.left, charBounds.top);
        charBox.setFillColor(sf::Color::Transparent);
        charBox.setOutlineColor(sf::Color::Transparent);
        charBox.setOutlineThickness(1.f);
        window.draw(charBox);
        if (showCollisionEffect && collisionEffectClock.getElapsedTime().asSeconds() < collisionEffectDuration) {
            window.clear(sf::Color(255, 0, 0, 150)); // Red flash
        }
        

        window.display();
    }

    return 0;
}
