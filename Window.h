//
// Created by shustrov38 on 29.06.2021.
//

#ifndef SIMPLEGAMEENGINE_WINDOW_H
#define SIMPLEGAMEENGINE_WINDOW_H

#include"SFML/Window.hpp"
#include <SFML/Graphics.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <memory>

class Window {
public:
    Window();

    Window(std::string_view title, const sf::Vector2u &size);

    ~Window();

    void beginDraw();

    void endDraw();

    virtual void update();

    bool isDone();

    bool isFullScreen();

    sf::RenderWindow *getRenderWindow();

    sf::Vector2u getWindowSize();

    void toggleFullScreen();

    void draw(sf::Drawable &drawable);

private:
    void setup(std::string_view title, const sf::Vector2u &size);

    void create();

    void destroy();

    sf::RenderWindow m_window;
    sf::Vector2u m_windowSize;
    std::string m_windowTitle;

    bool m_isDone;
    bool m_isFullScreen;
};

#endif //SIMPLEGAMEENGINE_WINDOW_H
