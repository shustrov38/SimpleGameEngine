//
// Created by shustrov38 on 24.07.2021.
//

#include "Player.h"

#include <cmath>

#include "Utilities.h"
#include "Wall.h"

Player::Player() {
    className = typeid(this).name();

    m_fillColor = sf::Color::Green;
    m_outlineColor = sf::Color::White;
    m_outlineThickness = 2;

    m_modelRadius = 10;

    m_viewDistance = 200;
    m_viewAngle = 100; // degrees
    m_viewResolution = 50;

    // normalize input parameters
    m_viewAngle = utl::degrees2radians(m_viewAngle);
    m_viewResolution += m_viewResolution & 1 ^ 1;

    m_viewBoundaryPoints.resize(m_viewResolution);

    m_polygon.setRadius(m_modelRadius);
    applyColors();
}

void Player::render(Window *window) {
    for (const auto &coord : m_viewBoundaryPoints) {
        sf::VertexArray line(sf::Lines, 2);
        line[0].position = m_position;
        line[1].position = coord;
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
    static const float step = utl::degrees2radians(5);
    const float phi = utl::angle(m_viewDirection) + float(direction) * step;
    m_viewDirection = sf::Vector2f(std::cos(phi), std::sin(phi));
}

void Player::move(const sf::Vector2f &offset) {
    m_polygon.move(offset);
    m_position += offset;
}

std::vector<sptr<Object>> Player::getCollisionCandidates(const std::vector<sptr<Object>> &worldObjects) {
    std::vector<sptr<Object>> candidates;

    float minx, miny, maxx, maxy;
    minx = maxx = m_position.x;
    miny = maxy = m_position.y;

    for (const auto &coord : m_viewBoundaryPoints) {
        maxx = std::max(maxx, coord.x);
        minx = std::min(minx, coord.x);
        maxy = std::max(maxy, coord.y);
        miny = std::min(miny, coord.y);
    }

    const auto lineRect = sf::FloatRect(minx, miny, maxx - minx, maxy - miny);

    for (const auto &object : worldObjects) {
        if (object->getClassName() != typeid(Wall *).name()) continue;

        auto wall = std::dynamic_pointer_cast<Wall>(object);
        auto rect = wall->getPolygon().getLocalBounds();

        if (rect.intersects(lineRect)) {
            candidates.emplace_back(wall);
        }
    }

    return candidates;
}

void Player::resetRays() {
    float step = m_viewAngle / float(m_viewResolution);
    float directionAngle = utl::angle(m_viewDirection);
    float alpha = directionAngle - float(m_viewResolution - 1) / 2 * step;

    for (int i = 0; i < m_viewResolution; ++i) {
        m_viewBoundaryPoints[i] = m_position + m_viewDistance * sf::Vector2f(std::cos(alpha), std::sin(alpha));
        alpha += step;
    }
}

void Player::look(const std::vector<sptr<Object>> &candidates) {
    resetRays();

    for (const auto &polygon : candidates) {

        const auto wall = std::dynamic_pointer_cast<Wall>(polygon);
        const auto poly = wall->getPolygon();

        for (auto &rayPoint: m_viewBoundaryPoints) {

            std::optional<sf::Vector2f> intersectionPoint = std::nullopt;

            for (int i = 0; i <= poly.getPointCount(); ++i) {

                const auto firstBoundaryPoint = poly.getPoint((i) % poly.getPointCount());
                const auto secondBoundaryPoint = poly.getPoint((i + 1) % poly.getPointCount());

                auto point = utl::castRayToBoundary(m_position, rayPoint, firstBoundaryPoint, secondBoundaryPoint);

                if (!point.has_value()) continue;

                float prevDist = utl::distance(m_position, intersectionPoint.value_or(point.value()));
                float newDist = utl::distance(m_position, point.value());

                if (newDist <= m_viewDistance && (!intersectionPoint.has_value() || newDist < prevDist)) {
                    intersectionPoint = point.value();
                }
            }

            rayPoint = intersectionPoint.value_or(rayPoint);
        }
    }
}
