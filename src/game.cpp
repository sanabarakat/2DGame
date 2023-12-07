/*
 * File: game.cpp
 * Author: Alessandra Gorla
 * Date: November 21, 2023
 * Description: Game class to deal with initialization and controller of 2D my game application.
 */
#include "game.h"

const float Game::SCENE_WIDTH = 800.0f;
const float Game::SCENE_HEIGHT = 600.0f;
const float Game::PLAYER_START_X = 400.0f;
const float Game::PLAYER_START_Y = 300.0f;
const float Game::RADIUS = 40.0f;

Game::Game() {
    initWindow();
    initBackground();
    initPlayer();
}

int Game::initWindow() {
    window.create(sf::VideoMode(SCENE_WIDTH, SCENE_HEIGHT), "My 2D game");
    window.setFramerateLimit(120);
    return 0;
}

int Game::initBackground() {
    if (!backgroundTexture.loadFromFile("resources/background.png")) {
        return 1;
    }
    backgroundTexture.setRepeated(true);
    background.setTexture(backgroundTexture);
    background.setTextureRect(sf::IntRect(0, 0, SCENE_WIDTH, SCENE_HEIGHT));
    return 0;
}

int Game::initPlayer() {
    player.setRadius(RADIUS);
    player.setOrigin(RADIUS, RADIUS);
    player.setPosition(PLAYER_START_X, PLAYER_START_Y);
    if (!playerTexture.loadFromFile("resources/pacman.png")) {
        return 1;
    }
    player.setTexture(&playerTexture);
    return 0;
}

void Game::processInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Left) {
                    player.move(-PLAYER_SPEED, 0);
                } else if (event.key.code == sf::Keyboard::Right) {
                    player.move(PLAYER_SPEED, 0);
                } else if (event.key.code == sf::Keyboard::Up) {
                    player.move(0, -PLAYER_SPEED);
                } else if (event.key.code == sf::Keyboard::Down) {
                    player.move(0, PLAYER_SPEED);
                }
                break;
            default:
                break;
        }
    }
}

void Game::update() {
    sf::Vector2f position = player.getPosition();
    if (position.x - RADIUS < 0) {
        position.x = RADIUS;
    }
    if (position.x + RADIUS > SCENE_WIDTH) {
        position.x = SCENE_WIDTH - RADIUS;
    }
    if (position.y - RADIUS < 0) {
        position.y = RADIUS;
    }
    if (position.y + RADIUS > SCENE_HEIGHT) {
        position.y = SCENE_HEIGHT - RADIUS;
    }
    player.setPosition(position);
}

void Game::render() {
    window.clear(sf::Color::White);
    window.draw(background);
    window.draw(player);
    window.display();
}

int Game::run() {
    while (window.isOpen()) {
        processInput();
        update();
        render();
    }
    return 0;
}
