//
// Created by shustrov38 on 01.07.2021.
//

#ifndef SIMPLEGAMEENGINE_WORLD_H
#define SIMPLEGAMEENGINE_WORLD_H

#include "Object.h"
#include "Player.h"
#include "Wall.h"

template<class T> using sptr = std::shared_ptr<T>;

class World {
public:
    World();

    ~World();

    void render(Window *window);

    void update();

    void handleInput();

private:
    Player player;
    std::vector<sptr<Object>> m_worldObjects;
};

#endif //SIMPLEGAMEENGINE_WORLD_H
