//
// Created by shustrov38 on 24.07.2021.
//

#include "Player.h"

#include <cmath>

#include "Utilities.h"
#include "Wall.h"
#include "MinimapBorder.h"
#include "Enumerated.h"


/*!
 * WARNING
 *
 * Turning _DEBUG on might cause huge performance drops
 *
 * WARNING
 */
#ifdef _DEBUG
#define debug std::cout
#else
#define debug 0 && std::cout
#endif

Player::Player() {
    className = typeid(this).name();

    m_fillColor = sf::Color::Green;
    m_outlineColor = sf::Color::White;
    m_outlineThickness = 2;

    m_modelRadius = 4;

    m_viewDistance = 200;
    m_viewAngle = 80; // degrees
    m_viewResolution = 300;

    // normalize input parameters
    m_viewAngle = utl::degrees2radians(m_viewAngle);
    m_viewResolution += m_viewResolution & 1 ^ 1;

    m_viewRayPoints.resize(m_viewResolution);
    m_viewRayIsUsed.resize(m_viewResolution);

    m_polygon.setRadius(m_modelRadius);
    applyColors();
}

void Player::render(Window *window) {
//    for (const auto &coord : m_viewRayPoints) {
//        sf::VertexArray line(sf::Lines, 2);
//        line[0].position = m_position;
//        line[1].position = coord;
//        window->draw(line);
//    }
    sf::VertexArray line(sf::Lines, 2);
    line[0].position = m_position;

    line[1].position = m_viewRayPoints.front();
    window->draw(line);
    line[1].position = m_viewRayPoints.back();
    window->draw(line);

    for (int i = 1; i < m_viewRayPoints.size(); ++i) {
        line[0].position = m_viewRayPoints[i - 1];
        line[1].position = m_viewRayPoints[i];
        window->draw(line);
    }

    window->draw(m_polygon);
}

void Player::setPosition(const sf::Vector2f &newPosition) {
    /*
     * the use of the delta is due to the fact that I want the coordinates of the circle
     * to be the coordinates of its center.
     */
    sf::Vector2f delta(m_modelRadius, m_modelRadius);
    m_polygon.setPosition(newPosition - delta);
    m_position = newPosition;
}

void Player::rotate(int direction) {
    m_viewDirection = utl::increasedAngle(m_viewDirection, float(direction) * 5);
}

void Player::move(const sf::Vector2f &offset) {
    m_polygon.move(offset);
    m_position += offset;
}

void Player::updateCollisionCandidates(const vecPObject &worldObjects) {
    const static std::vector<std::string> collidableClasses = {
            typeid(Wall *).name(),
            typeid(MinimapBorder *).name()
    };

    m_collisionCandidates.clear();

    float minx, miny, maxx, maxy;
    minx = maxx = m_position.x;
    miny = maxy = m_position.y;

    for (const auto &coord : m_viewRayPoints) {
        maxx = std::max(maxx, coord.x);
        minx = std::min(minx, coord.x);
        maxy = std::max(maxy, coord.y);
        miny = std::min(miny, coord.y);
    }


    const auto lineRect = sf::FloatRect(minx, miny, maxx - minx, maxy - miny);

    for (const auto &object : worldObjects) {
        if (std::find(collidableClasses.begin(), collidableClasses.end(), object->getClassName()) ==
            collidableClasses.end())
            continue;

        auto wall = std::dynamic_pointer_cast<Wall>(object);
        auto rect = wall->getPolygon().getLocalBounds();

        if (rect.intersects(lineRect)) {
            m_collisionCandidates.emplace_back(wall);
        }
    }
}

void Player::resetRays() {
    float step = m_viewAngle / float(m_viewResolution);
    float directionAngle = utl::angle(m_viewDirection);
    float alpha = directionAngle - float(m_viewResolution - 1) / 2 * step;

    for (int i = 0; i < m_viewResolution; ++i) {
        m_viewRayIsUsed[i] = false;
        m_viewRayPoints[i] = m_position + m_viewDistance * sf::Vector2f(std::cos(alpha), std::sin(alpha));
        alpha += step;
    }
}

void Player::look() {
    resetRays();
    m_objectsPlayerSee.clear();

    for (const auto [polygonIndex, polygon] : enumerated(m_collisionCandidates)) {

        const auto wall = std::dynamic_pointer_cast<Wall>(polygon);
        const auto poly = wall->getPolygon();

        bool isCollidedWithPolygon = false;

        debug << "Polygon " << polygonIndex << ":" << std::endl;

        for (auto[rayPointIndex, rayPoint]: enumerated(m_viewRayPoints)) {
            debug << "\tRay " << rayPointIndex << ":" << std::endl;

            sf::Vector2f intersectionPoint = rayPoint;

            for (int i = 0; i < poly.getPointCount(); ++i) {
                debug << "\t\tPolygon segment ["
                          << (i + 0) % poly.getPointCount() << " "
                          << (i + 1) % poly.getPointCount() << "]:"
                          << std::endl;

                const auto firstBoundaryPoint = poly.getPoint((i + 0) % poly.getPointCount());
                const auto secondBoundaryPoint = poly.getPoint((i + 1) % poly.getPointCount());

                auto castResult = utl::castRayToBoundary(m_position, rayPoint, firstBoundaryPoint, secondBoundaryPoint);

                if (!castResult.has_value()) {
                    debug << "\t\t\tcontinue" << std::endl;
                    continue;
                }

                const auto point = castResult.value();

                debug << "\t\t\tcasted -> (" << point.x << ' ' << point.y << ")" << std::endl;

                const float prevDist = utl::distance(m_position, intersectionPoint);
                const float newDist = utl::distance(m_position, point);

                debug << "\t\t\tdistance -> " << newDist << std::endl;

                // there is no need to check the condition (newDist <= m_viewDistance) because
                // intersection point is always equal to the correct ray point
                if (newDist <= prevDist) {
                    debug << "\t\t\t\tdistance changed" << std::endl;
                    isCollidedWithPolygon = true;
                    intersectionPoint = point;
                }
            }

            // update ray if got new collision point
            if (rayPoint != intersectionPoint) {
                rayPoint = intersectionPoint;
                m_viewRayIsUsed[rayPointIndex] = true;
            }
        }

        if (isCollidedWithPolygon) {
            m_objectsPlayerSee.emplace_back(polygon);
        }
    }
}

const std::vector<sf::Vector2f> &Player::getMViewRayPoints() const {
    return m_viewRayPoints;
}

size_t Player::getMViewResolution() const {
    return m_viewResolution;
}

const vecPObject &Player::getMObjectsPlayerSee() const {
    return m_objectsPlayerSee;
}

const std::vector<bool> &Player::getMViewRayIsUsed() const {
    return m_viewRayIsUsed;
}

float Player::getMViewDistance() const {
    return m_viewDistance;
}

sf::Vector2f Player::getMPosition() const {
    return m_position;
}

void Player::handleInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        rotate(ROTATE_LEFT);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        rotate(ROTATE_RIGHT);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        move(STEP_SIZE * utl::increasedAngle(m_viewDirection, 0));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        move(STEP_SIZE * utl::increasedAngle(m_viewDirection, 180));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        move(STEP_SIZE * utl::increasedAngle(m_viewDirection, -90));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        move(STEP_SIZE * utl::increasedAngle(m_viewDirection, 90));
    }
}
