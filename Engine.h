//
// Created by shustrov38 on 29.06.2021.
//

#ifndef SIMPLEGAMEENGINE_ENGINE_H
#define SIMPLEGAMEENGINE_ENGINE_H

#include "Window.h"
#include "World.h"

class Engine {
public:
    Engine();

    Engine(std::string_view title, sf::Vector2u &size);

    ~Engine();

    void handleInput();

    void update();

    void render();

    bool isDone();

    Window *getWindow();

    sf::Time getElapsedTime();

    void restartClock();

private:
    Window m_window;
    World m_world;

    float m_elapsedTime;
    sf::Clock m_clock;
};

#endif //SIMPLEGAMEENGINE_ENGINE_H
