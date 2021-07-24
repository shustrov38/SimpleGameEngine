//
// Created by shustrov38 on 24.07.2021.
//

#ifndef SIMPLEGAMEENGINE_POLYGON_H
#define SIMPLEGAMEENGINE_POLYGON_H

#include "Object.h"

class Polygon : public WorldObject<sf::ConvexShape> {
public:
    explicit Polygon(const std::vector<sf::Vector2f> &points);

    void move(const sf::Vector2f &offset) override;

private:
    void setPosition(const sf::Vector2f &newPosition) override;
};


#endif //SIMPLEGAMEENGINE_POLYGON_H
