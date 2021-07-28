//
// Created by shustrov38 on 27.07.2021.
//

#include "MinimapBorder.h"

MinimapBorder::MinimapBorder(const std::vector<sf::Vector2f> &points) : Wall(points) {
    className = typeid(this).name();

    m_fillColor = sf::Color::Black;
    m_outlineColor = sf::Color::White;
    m_outlineThickness = 2;

    applyColors();
}
