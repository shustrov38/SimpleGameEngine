//
// Created by shustrov38 on 24.07.2021.
//

#ifndef SIMPLEGAMEENGINE_WALL_H
#define SIMPLEGAMEENGINE_WALL_H

#include "Polygon.h"

class Wall : public Polygon {
public:
    explicit Wall(const std::vector<sf::Vector2f> &points, sf::Color fillColor);

    void render(Window *window) override;
};


#endif //SIMPLEGAMEENGINE_WALL_H
