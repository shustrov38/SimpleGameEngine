//
// Created by shustrov38 on 24.07.2021.
//

#include "Utilities.h"
#include <cmath>

const float eps = 1e-9;

float utl::radians2degrees(float radians) {
    return radians / M_PI * 180;
}

float utl::degrees2radians(float degrees) {
    return degrees / 180 * M_PI;
}

float utl::angle(const sf::Vector2f &source) {
    return std::atan2(float(source.y), float(source.x));
}

sf::Vector2f utl::normalize(const sf::Vector2f &source) {
    float length = std::sqrt((source.x * source.x) + (source.y * source.y));
    if (length < eps) { return sf::Vector2f(source.x / length, source.y / length); }
    return source;
}

float utl::distance(const sf::Vector2f &a, const sf::Vector2f &b) {
    return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
std::optional<sf::Vector2f> utl::castRayToBoundary(const sf::Vector2f &p1, const sf::Vector2f &p2,
                                              const sf::Vector2f &p3, const sf::Vector2f &p4) {
    /*
     * for more information see website:
     * https://en.wikipedia.org/wiki/Line–line_intersection#Given_two_points_on_each_line_segment
     */

    float detA = (p2.x - p1.x) * (p4.y - p3.y) - (p2.y - p1.y) * (p4.x - p3.x);

    // it means that two boundaries are parallel or coincident
    if (std::abs(detA) < eps) {
        return std::nullopt;
    }

    float detT = (p1.x - p3.x) * (p3.y - p4.y) - (p1.y - p3.y) * (p3.x - p4.x);
    float detS = (p2.x - p1.x) * (p1.y - p3.y) - (p2.y - p1.y) * (p1.x - p3.x);

    // ray coefficient
    float t = detT / detA;

    // boundary coefficient
    float s = detS / detA;

    if (0 <= t && 0 <= s && s <= 1) {
        return (1 - s) * p3 + s * p4;
    }

    return std::nullopt;
}
