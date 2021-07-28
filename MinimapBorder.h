//
// Created by shustrov38 on 27.07.2021.
//

#ifndef SIMPLEGAMEENGINE_MINIMAPBORDER_H
#define SIMPLEGAMEENGINE_MINIMAPBORDER_H

#include "Wall.h"

class MinimapBorder : public Wall {
public:
    explicit MinimapBorder(const std::vector<sf::Vector2f> &points);
};


#endif //SIMPLEGAMEENGINE_MINIMAPBORDER_H
