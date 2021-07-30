//
// Created by shustrov38 on 01.07.2021.
//

#include "World.h"

World::World() {
    // set up world objects (including world borders)

    vecCoord borderRect = {
            {0,   0},
            {200, 0},
            {200, 200},
            {0,   200}
    };
    m_worldObjects.emplace_back(std::make_shared<MinimapBorder>(borderRect, sf::Color::Red));

    vecCoord bigTriangle = {
            {40,  40},
            {100, 50},
            {20,  150}
    };
    m_worldObjects.emplace_back(std::make_shared<Wall>(bigTriangle, sf::Color::Cyan));

    vecCoord tinyTriangle = {
            {150, 150},
            {170, 150},
            {150, 180}
    };
    m_worldObjects.emplace_back(std::make_shared<Wall>(tinyTriangle, sf::Color::Magenta));

    player.setPosition({100, 100});
}

World::~World() {

}

void World::render(Window *window) {
    player.renderPseudo3D(window);

//    for (const auto &worldObject : m_worldObjects) {
//        worldObject->render(window);
//    }
//
    player.render(window);
}

void World::update() {
    player.look(m_worldObjects);
}

void World::handleInput() {
    player.handleInput();
}
