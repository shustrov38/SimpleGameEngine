//
// Created by shustrov38 on 24.07.2021.
//

#include "Player.h"

#include <cmath>
#include <iomanip>

#include "Utilities.h"
#include "Enumerated.h"


/*!
 * WARNING
 * Turning _DEBUG on might cause huge performance drops
 * WARNING
 */
#ifdef _DEBUG
#define debug std::cout
#else
#define debug 0 && std::cout
#endif

const std::vector<std::string> Player::collidableClasses = {
        typeid(Wall *).name(),
        typeid(MinimapBorder *).name()
};

Player::Player() {
    className = typeid(this).name();

    m_fillColor = sf::Color::Green;
    m_outlineColor = sf::Color::White;
    m_outlineThickness = 2;

    m_modelRadius = 4;

    m_viewDistance = 300.f;
    m_viewAngle = 60.f; // degrees
    m_viewResolution = 100;
    m_viewProjectionDistance = 10.f;

    // normalize input parameters
    m_viewAngle = utl::degrees2radians(m_viewAngle);
    m_viewResolution += m_viewResolution & 1 ^ 1;

    m_viewRayPoints.resize(m_viewResolution);
    m_viewParameters.resize(m_viewResolution);

    m_polygon.setRadius(m_modelRadius);
    applyColors();

    resetRays();
}

void Player::render(Window *window) {
    sf::VertexArray line(sf::Lines, 2);
    line[0].position = m_position;

    line[1].position = m_viewRayPoints.front();
    window->draw(line);
    line[1].position = m_viewRayPoints.back();
    window->draw(line);

    for (int i = 1; i < m_viewRayPoints.size(); ++i) {
        line[0].position = m_viewRayPoints[i - 1];
        line[1].position = m_viewRayPoints[i];
        window->draw(line);
    }

    window->draw(m_polygon);
}

void Player::renderPseudo3D(Window *window) {
    auto[width, height] = sf::Vector2f(window->getWindowSize());

    float rectWidth = width / m_viewResolution;

    for (const auto &[i, collisionPoint] : enumerated(m_viewRayPoints)) {
        if (!m_viewParameters[i].has_value()) continue;

        float rayAngle = utl::angle(collisionPoint - m_position);
        float viewDirectionAngle = utl::angle(m_viewDirection);
        float cosineCoefficient = std::cos(rayAngle - viewDirectionAngle);

        float trueDistance = utl::distance(m_position, collisionPoint);
        float projectionDistance = trueDistance * cosineCoefficient;

        float distanceCoefficient = m_viewProjectionDistance / projectionDistance;

        float rectHeight = 1000.f * distanceCoefficient;

        sf::RectangleShape rect({rectWidth, rectHeight});
        rect.setPosition({rectWidth * i, (height - rectHeight) / 2});

        auto color = m_viewParameters[i]->color;
        float colorCoefficient = 1.f - utl::distance(m_position, collisionPoint) / m_viewDistance;
        color.a = sf::Uint8(255.f * colorCoefficient);
        rect.setFillColor(color);

        window->draw(rect);
    }
}

void Player::setPosition(const sf::Vector2f &newPosition) {
    /*
     * the use of the delta is due to the fact that I want the coordinates of the circle
     * to be the coordinates of its center.
     */
    sf::Vector2f delta(m_modelRadius, m_modelRadius);
    m_polygon.setPosition(newPosition - delta);
    m_position = newPosition;
}

void Player::rotate(int direction) {
    m_viewDirection = utl::increasedAngle(m_viewDirection, float(direction) * 5);
}

void Player::move(const sf::Vector2f &offset) {
    m_polygon.move(offset);
    m_position += offset;
}

void Player::resetRays() {
    float step = m_viewAngle / float(m_viewResolution);
    float directionAngle = utl::angle(m_viewDirection);
    float alpha = directionAngle - float(m_viewResolution - 1) / 2 * step;

    for (int i = 0; i < m_viewResolution; ++i) {
        m_viewRayPoints[i] = m_position + m_viewDistance * sf::Vector2f(std::cos(alpha), std::sin(alpha));
        alpha += step;
    }
}

void Player::look(const vecPObject &objects) {
    resetRays();
    for (auto &e: m_viewParameters) e.reset();

    auto processBoundary = [&](const sptr<Object> &polygon, const sf::Vector2f &a, const sf::Vector2f &b) -> void {
        const auto poly = std::dynamic_pointer_cast<Wall>(polygon);
        auto polyColor = poly->getMFillColor();

        // cast all rays to current boundary
        for (const auto &[i, rayPoint]: enumerated(m_viewRayPoints)) {
            auto castResult = utl::castRayToBoundary(m_position, rayPoint, a, b);
            auto point = castResult.value_or(rayPoint);
            auto prevDist = utl::distance(m_position, rayPoint);
            auto newDist = utl::distance(m_position, point);
            if (newDist < prevDist) {
                rayPoint = point;

                // update params
                m_viewParameters[i] = polygonParameters(poly);
            }
        }
    };

    utl::iterateAllPolygonBoundaries(objects, processBoundary);
}

const std::vector<sf::Vector2f> &Player::getMViewRayPoints() const {
    return m_viewRayPoints;
}

size_t Player::getMViewResolution() const {
    return m_viewResolution;
}

float Player::getMViewDistance() const {
    return m_viewDistance;
}

sf::Vector2f Player::getMPosition() const {
    return m_position;
}

const std::vector<std::optional<polygonParameters>> &Player::getMViewParameters() const {
    return m_viewParameters;
}

void Player::handleInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        rotate(ROTATE_LEFT);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        rotate(ROTATE_RIGHT);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        move(STEP_SIZE * utl::increasedAngle(m_viewDirection, 0));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        move(STEP_SIZE * utl::increasedAngle(m_viewDirection, 180));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        move(STEP_SIZE * utl::increasedAngle(m_viewDirection, -90));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        move(STEP_SIZE * utl::increasedAngle(m_viewDirection, 90));
    }
}
