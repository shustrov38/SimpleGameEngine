//
// Created by shustrov38 on 24.07.2021.
//

#ifndef SIMPLEGAMEENGINE_UTILITIES_H
#define SIMPLEGAMEENGINE_UTILITIES_H

#include"SFML/Window.hpp"
#include <SFML/Graphics.hpp>

#include <functional>

#include "Object.h"

namespace utl {
    /*!
     * @param radians - radians to convert
     * @return degrees
     */
    float radians2degrees(float radians);

    /*!
     * @param degrees - degrees to convert
     * @return radians
     */
    float degrees2radians(float degrees);

    /*!
     * @param source - radius vector
     * @param norm - if norm switch [-pi pi] -> [0, 2pi)
     * @return angle of the radius vector
     */
    float angle(const sf::Vector2f &source, bool norm = false);

    /*!
     * @param source - source angle
     * @param addition - angle to add
     * @return increased angle
     */
    sf::Vector2f increasedAngle(const sf::Vector2f &source, float addition);

    /*!
     * @param source - radius vector
     * @return normalized radius vector
     */
    sf::Vector2f normalize(const sf::Vector2f &source);

    /*!
     * @param a - first point
     * @param b - second point
     * @return (euclidean) distance between two points
     */
    float distance(const sf::Vector2f &a, const sf::Vector2f &b);

    /*!
     * @param p1 - ray start point
     * @param p2 - ray through point
     * @param p3 - first boundary point
     * @param p4 - second boundary point
     * @return intersection point (optional)
     */
    std::optional<sf::Vector2f> castRayToBoundary(const sf::Vector2f &p1, const sf::Vector2f &p2,
                                                  const sf::Vector2f &p3, const sf::Vector2f &p4);

    /*!
     * @param p - point
     * @param p1 - first boundary point
     * @param p2 - second boundary point
     * @return true if point belongs to boundary, otherwise false
     */
    bool isPointBelongsToBoundary(const sf::Vector2f &p, const sf::Vector2f &p1, const sf::Vector2f &p2);

    /*!
     * @param func
     */
    void iterateAllPolygonBoundaries(const vecPObject &objects,
                                     std::function<void(const sptr<Object> &,
                                                        const sf::Vector2f &,
                                                        const sf::Vector2f &)> &&func);


}

#endif //SIMPLEGAMEENGINE_UTILITIES_H
