//
// Created by shusrov38t on 24.07.2021.
//

#ifndef SIMPLEGAMEENGINE_PLAYER_H
#define SIMPLEGAMEENGINE_PLAYER_H

#include "Object.h"
#include "Wall.h"
#include "MinimapBorder.h"

class Player : public WorldObject<sf::CircleShape> {
public:
    static const std::vector<std::string> collidableClasses;

    static const int ROTATE_LEFT = -1;
    static const int ROTATE_RIGHT = 1;

    static constexpr float STEP_SIZE = 3;

    explicit Player();

    void render(Window *window) override;

    void renderPseudo3D(Window *window);

    void setPosition(const sf::Vector2f &newPosition) override;

    void look(const vecPObject &objects);

    const std::vector<sf::Vector2f> &getMViewRayPoints() const;

    void rotate(int direction);

    void move(const sf::Vector2f &offset) override;

    size_t getMViewResolution() const;

    float getMViewDistance() const;

    sf::Vector2f getMPosition() const;

    const std::vector<std::optional<polygonParameters>> &getMViewParameters() const;

    void handleInput();

private:
    void resetRays();

protected:
    float m_modelRadius;

    // render logic variables

    sf::Vector2f m_viewDirection = {1, 0};
    float m_viewDistance;
    float m_viewAngle;
    size_t m_viewResolution;
    float m_viewProjectionDistance;

    vecCoord m_viewRayPoints;
    std::vector<std::optional<polygonParameters>> m_viewParameters;
};


#endif //SIMPLEGAMEENGINE_PLAYER_H
