#include "score.h"
#include <iostream>
#include <fstream>

void score::initialize() {
    score = 0.0;
    scoreAdd = 0.555;
    highScore = 0;
    scoreClock.restart();

    if (!font.loadFromFile("pixel.ttf")) {
        std::cout << " Failed to load font.ttf" << std::endl;
    }
    load();
}

void score::save()
{
    std::ofstream output("highscore.txt");
    if (output.is_open()) {
        output << highScore;
        output.close();
    }
}

void score::load() {
    std::ifstream input("highscore.txt");
    if (input.is_open()) {
        input >> highScore;
        input.close();
    }
    else {
        highScore = 0;
    }
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
