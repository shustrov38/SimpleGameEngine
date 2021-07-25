//
// Created by shustrov38 on 29.06.2021.
//

#define DEFAULT_WINDOW_WIDTH 640
#define DEFAULT_WINDOW_HEIGHT 480

#define DEFAULT_WINDOW_TITLE "Window"

#include "Window.h"

Window::Window() {
    setup(DEFAULT_WINDOW_TITLE, sf::Vector2u(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT));
}

Window::Window(std::string_view title, const sf::Vector2u &size) {
    setup(title, size);
}

Window::~Window() {
    destroy();
}

void Window::beginDraw() {
    m_window.clear(sf::Color::Black);
}

void Window::endDraw() {
    m_window.display();
}

void Window::update() {
    sf::Event event{};
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_isDone = true;
        } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F11) {
            toggleFullScreen();
        }
    }
}

bool Window::isDone() {
    return m_isDone;
}

bool Window::isFullScreen() {
    return m_isFullScreen;
}

sf::RenderWindow *Window::getRenderWindow() {
    return &m_window;
}

sf::Vector2u Window::getWindowSize() {
    return m_windowSize;
}

void Window::toggleFullScreen() {
    m_isFullScreen = !m_isFullScreen;
    destroy();
    create();
}

void Window::draw(sf::Drawable &drawable) {
    m_window.draw(drawable);
}

void Window::setTitle(std::string_view newTitle) {
    m_window.setTitle(newTitle.data());
}

void Window::setup(std::string_view title, const sf::Vector2u &size) {
    m_window.setFramerateLimit(60);
    m_windowTitle = title;
    m_windowSize = size;
    m_isFullScreen = false;
    m_isDone = false;
    create();
}

void Window::destroy() {
    m_window.close();
}

void Window::create() {
    auto style = (m_isFullScreen ? sf::Style::Fullscreen : sf::Style::Default);
    m_window.create({m_windowSize.x, m_windowSize.y, 32}, m_windowTitle, style);
}
