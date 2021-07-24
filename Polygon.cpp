//
// Created by shustrov38 on 24.07.2021.
//

#include "Polygon.h"

Polygon::Polygon(const std::vector<sf::Vector2f> &points) {
    m_polygon.setPointCount(points.size());

    for (int i = 0; i < points.size(); ++i) {
        m_polygon.setPoint(i, points[i]);
    }
}

void Polygon::setPosition(const sf::Vector2f &newPosition) {
    /*
     * I want to work only with absolute coordinates of polygon, so I must not update position of polygon.
     */
    throw std::runtime_error("Function setPosition is not allowed for <Polygon*>.");
}

void Polygon::move(const sf::Vector2f &offset) {
    /*
     * I want to work only with absolute coordinates of polygon, so I must not update position of polygon.
     */
    for (int i = 0; i < m_polygon.getPointCount(); ++i) {
        auto prevPoint = m_polygon.getPoint(i);
        m_polygon.setPoint(i, prevPoint + offset);
    }

    m_position += offset;
}