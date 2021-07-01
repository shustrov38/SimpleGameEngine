//
// Created by shustrov38 on 29.06.2021.
//

#include "Engine.h"

Engine::Engine() : m_window() {}

Engine::Engine(std::string_view title, sf::Vector2u &size) : m_window(title, size) {}

Engine::~Engine() {
    m_window.~Window();
}

void Engine::handleInput() {

}

void Engine::update() {
    m_window.update();
    float timeStep = 1.0f / 30;

    if (m_elapsedTime >= timeStep) {
        m_elapsedTime -= timeStep;
    }
}

void Engine::render() {
    m_window.beginDraw();

    // draw

    m_window.endDraw();
}

bool Engine::isDone() {
    return m_window.isDone();
}

Window *Engine::getWindow() {
    return &m_window;
}

sf::Time Engine::getElapsedTime() {
    return m_clock.getElapsedTime();
}

void Engine::restartClock() {
    m_elapsedTime += m_clock.restart().asSeconds();
}

