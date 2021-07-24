//
// Created by shustrov38 on 01.07.2021.
//

#include "World.h"

World::World() {
    std::vector<sf::Vector2f> points = {
            {60, 0},
            {0,  0},
            {0, 60}
    };

    m_worldObjects.emplace_back(std::make_shared<Wall>(points));
    m_worldObjects.back()->move({200, 100});

    m_worldObjects.emplace_back(std::make_shared<Wall>(points));
    m_worldObjects.back()->move({350, 200});


    player.setPosition({300, 300});
}

World::~World() {

}

void World::render(Window *window) {
    for (const auto &worldObject : m_worldObjects) {
        worldObject->render(window);
    }

//    for (const auto &wall : player.getCollisionCandidates(m_worldObjects)) {
//        wall->render(window);
//    }

    player.render(window);
}

void World::update() {
    const auto candidates = player.getCollisionCandidates(m_worldObjects);
    player.look(candidates);
}

void World::handleInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        player.rotate(Player::ROTATE_LEFT);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        player.rotate(Player::ROTATE_RIGHT);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        player.move(sf::Vector2f(0, -Player::STEP_SIZE));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        player.move(sf::Vector2f(0, Player::STEP_SIZE));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        player.move(sf::Vector2f(-Player::STEP_SIZE, 0));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        player.move(sf::Vector2f(Player::STEP_SIZE, 0));
    }
}
