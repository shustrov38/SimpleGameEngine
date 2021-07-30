//
// Created by shustrov38 on 01.07.2021.
//

#ifndef SIMPLEGAMEENGINE_OBJECT_H
#define SIMPLEGAMEENGINE_OBJECT_H

#include "Window.h"
#include <vector>

class Object;

template<class T> using sptr = std::shared_ptr<T>;
using vecPObject = std::vector<sptr<Object>>;
using vecCoord = std::vector<sf::Vector2f>;

class Object {
public:
    virtual std::string getClassName() final {
        return className;
    }

    virtual void render(Window *window) = 0;

    virtual void setPosition(const sf::Vector2f &newPosition) = 0;

    virtual void move(const sf::Vector2f &offset) = 0;

protected:
    std::string className;

    sf::Vector2f m_position = {0, 0};
};

template<class T>
class WorldObject : public Object {
    static_assert(std::is_base_of<sf::Shape, T>::value, "T must be derived from sf::Shape class.\n");

public:
    void applyColors() {
        m_polygon.setFillColor(m_fillColor);
        m_polygon.setOutlineColor(m_outlineColor);
        m_polygon.setOutlineThickness(m_outlineThickness);
    }

    T getPolygon() {
        return m_polygon;
    }

    const sf::Color &getMFillColor() const {
        return m_fillColor;
    }

protected:
    // geometry
    T m_polygon;

    // graphics
    sf::Color m_fillColor = sf::Color::Red;
    sf::Color m_outlineColor = sf::Color::White;
    float m_outlineThickness = 1;
};

#endif //SIMPLEGAMEENGINE_OBJECT_H
