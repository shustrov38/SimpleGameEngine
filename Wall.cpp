//
// Created by shustrov38 on 24.07.2021.
//

#include "Wall.h"

Wall::Wall(const std::vector<sf::Vector2f> &points) : Polygon(points) {
    className = typeid(this).name();

    m_fillColor = sf::Color::Red;
    m_outlineColor = sf::Color::White;
    m_outlineThickness = 1;

    applyColors();
}

void Wall::render(Window *window) {
    window->draw(m_polygon);
}
