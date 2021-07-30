//
// Created by shustrov38 on 24.07.2021.
//

#include "Wall.h"

Wall::Wall(const std::vector<sf::Vector2f> &points, sf::Color fillColor) : Polygon(points, fillColor) {
    className = typeid(this).name();

    applyColors();
}

void Wall::render(Window *window) {
    window->draw(m_polygon);
}
