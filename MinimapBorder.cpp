//
// Created by shustrov38 on 27.07.2021.
//

#include "MinimapBorder.h"

MinimapBorder::MinimapBorder(const std::vector<sf::Vector2f> &points, sf::Color fillColor) : Wall(points, fillColor) {
    className = typeid(this).name();

    applyColors();
}
