//
// Created by shustrov38 on 01.07.2021.
//

#include "World.h"
#include "Utilities.h"
#include "MinimapBorder.h"

using vecCoord = std::vector<sf::Vector2f>;

World::World() {
    // set up world objects (including world borders)

    vecCoord borderRect = {
            {0,   0},
            {200, 0},
            {200, 200},
            {0,   200}
    };
    m_worldObjects.emplace_back(std::make_shared<MinimapBorder>(borderRect));

    vecCoord bigTriangle = {
            {40,  40},
            {100, 50},
            {20,  150}
    };
    m_worldObjects.emplace_back(std::make_shared<Wall>(bigTriangle));

    vecCoord tinyTriangle = {
            {150, 150},
            {170, 150},
            {150, 180}
    };
    m_worldObjects.emplace_back(std::make_shared<Wall>(tinyTriangle));

    player.setPosition({100, 100});
}

World::~World() {

}

void World::render(Window *window) {
    const auto windowSize = window->getWindowSize();
    const int width = int(windowSize.x);
    const int height = int(windowSize.y);

    const int viewResolution = (int) player.getMViewResolution();
    const float viewDistance = player.getMViewDistance();

    const int boxWidth = (width + viewResolution - 1) / viewResolution;

    std::vector<int> rectX(viewResolution);

    int delta = width / 2 - viewResolution / 2 * boxWidth;
    for (int i = 0; i < viewResolution; ++i) {
        rectX[i] = i * boxWidth + delta;
    }

    const auto rays = player.getMViewRayPoints();
    const auto used = player.getMViewRayIsUsed();

    for (int i = 0; i < viewResolution; ++i) {
        if (!used[i]) continue;
        float distanceCoefficient = 10.f / utl::distance(player.getMPosition(), rays[i]);

        float boxHeight = 1000.f * distanceCoefficient;
        sf::RectangleShape rect(sf::Vector2f(float(boxWidth), boxHeight));
        rect.setPosition(sf::Vector2f(float(rectX[i]), (height - boxHeight) / 2));

        float colorCoefficient = 1.f - utl::distance(player.getMPosition(), rays[i]) / viewDistance;
        rect.setFillColor(sf::Color(255, 0, 0, sf::Uint8(255.f * colorCoefficient)));

        window->draw(rect);
    }

    for (const auto &worldObject : m_worldObjects) {
        worldObject->render(window);
    }

    player.render(window);
}

void World::update() {
    player.updateCollisionCandidates(m_worldObjects);
    player.look();
}

void World::handleInput() {
    player.handleInput();
}
