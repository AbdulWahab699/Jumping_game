#include <SFML/Graphics.hpp>
#include <iostream>
#include "obstacles.h"
#include "animation.h"
#include "score.h"
#include "pathway.h"
#include "backgound.h"
#include <vector>
#include <memory>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 480), "DASH TILL' YOU CRASH");
    window.setFramerateLimit(60);
    sf::Clock deltaClock;

    int gameState = 0;  // 0 = Start, 1 = Playing, 2 = Game Over

    // Interface Textures
    sf::Texture gameStartTexture, gameOverTexture;
    sf::Sprite gameStartSprite, gameOverSprite;

    if (gameStartTexture.loadFromFile("obstacles-1/Front-intreface.png"))
        gameStartSprite.setTexture(gameStartTexture);
    if (gameOverTexture.loadFromFile("obstacles-1/Tryagain-interface.png"))
        gameOverSprite.setTexture(gameOverTexture);


    // Game elements
    pathway pathway;
    score gameScore;
    backgound background;
    animation character;

    

    std::vector<std::shared_ptr<sf::Texture>> textures;
    std::vector<std::string> filepaths = {
        "obstacles-1/grass.png", "obstacles-1/boxAlt.png", "obstacles-1/boxCoin.png",
        "obstacles-1/boxExplosive.png", "obstacles-1/fence.png", "obstacles-1/dirt.png",
        "obstacles-1/boxWarning.png", "obstacles-1/spikes.png", "obstacles-1/boxItem_disabled.png",
        "obstacles-1/lock_Green.png"
    };

    for (const auto& path : filepaths) {
        auto tex = std::make_shared<sf::Texture>();
        if (tex->loadFromFile(path)) {
            tex->setSmooth(true);
            textures.push_back(tex);
        }
    }

    std::vector<obstacles> activeObstacles;
    sf::Clock spawnClock;
    float spawnDelay = 2.0f;
    int currentObstacleIndex = 0;

    // Physics
    float gravity = 981.f;
    float jumpForce = -620.f;
    bool isJumping = false;
    float velocityY = 0.f;
    float groundY = 300.f;

    // Reset everything
    auto resetGame = [&]() {
        activeObstacles.clear();
        gameScore.initialize();
        background.initialize();
        pathway.initialize();
        character.initialize();
        character.Sprite.setPosition(100.f, groundY);
        velocityY = 0.f;
        isJumping = false;
        spawnClock.restart();
        };

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                if (gameState == 0 || gameState == 2) {
                    resetGame();
                    gameState = 1;
                }
            }
        }

        float deltaTime = deltaClock.restart().asSeconds();

        if (gameState == 0) {
            // Start screen
            window.clear();
            window.draw(gameStartSprite);
            window.display();
            continue;
        }

        if (gameState == 2) {
            // Game over screen
            window.clear();
            window.draw(gameOverSprite);
            window.display();
            continue;
        }

        // === Playing State ===
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isJumping) {
            character.jumpSound.play();
            velocityY = jumpForce;
            isJumping = true;
        }

        // Gravity & movement
        velocityY += gravity * deltaTime;
        character.Sprite.move(0.f, velocityY * deltaTime);

        // Ground collision
        if (character.Sprite.getPosition().y >= groundY) {
            character.Sprite.setPosition(character.Sprite.getPosition().x, groundY);
            velocityY = 0.f;
            isJumping = false;
        }

        // Update animations
        if (isJumping)
            character.jumpUpdate();
        else
            character.update();

        // Spawn obstacles
        if (spawnClock.getElapsedTime().asSeconds() > spawnDelay) {
            obstacles ob;
            ob.initialize(textures[currentObstacleIndex], sf::Vector2f(800.f, 370.f));
            activeObstacles.push_back(ob);
            currentObstacleIndex = (currentObstacleIndex + 1) % textures.size();
            spawnClock.restart();
        }

        // Update obstacles & check collision
        for (auto& ob : activeObstacles) {
            ob.update(deltaTime);
            if (character.Sprite.getGlobalBounds().intersects(ob.getBounds())) {
                gameScore.save();  // Save high score
                gameState = 2;     // Game Over
            }
        }

        pathway.update();
        background.update();
        gameScore.update();

        // === DRAW ===
        window.clear(sf::Color::White);
        background.Draw(window);
        /*window.draw(pathSprite);*/
        pathway.Draw(window);
        character.Draw(window);
        gameScore.Draw(window);

        for (auto& ob : activeObstacles)
            ob.Draw(window);

        window.display();
    }

    return 0;
}
