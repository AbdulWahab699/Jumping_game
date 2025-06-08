#include "score.h"
#include <iostream>

void score::initialize() {
    score = 0.0;
    scoreAdd = 0.555;
    scoreClock.restart();

    if (!font.loadFromFile("font-maker.ttf")) {
        std::cout << " Failed to load font.ttf" << std::endl;
    }
}

void score::load() {
    // Not used here, but good for future assets if needed
}

void score::update() {
    if (scoreClock.getElapsedTime().asMilliseconds() >= 250) {
        score += scoreAdd;
        std::cout << "Score: " << score << std::endl;
        scoreClock.restart();
    }
}

void score::Draw(sf::RenderWindow& window) {
    sf::Text text;
    text.setFont(font);
    text.setString("Score: " + std::to_string((float)score));
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    text.setPosition(10.f, 10.f);
    window.draw(text);
}
