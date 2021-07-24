//
// Created by shusrov38t on 24.07.2021.
//

#ifndef SIMPLEGAMEENGINE_PLAYER_H
#define SIMPLEGAMEENGINE_PLAYER_H

#include "Object.h"

class Player : public WorldObject<sf::CircleShape> {
public:
    static const int ROTATE_LEFT = -1;
    static const int ROTATE_RIGHT = 1;

    static const int STEP_SIZE = 3;

    explicit Player();

    void render(Window *window) override;

    void setPosition(const sf::Vector2f &newPosition) override;

    void look(const std::vector<sptr<Object>> &candidates);

    void rotate(int direction);

    void move(const sf::Vector2f &offset) override;

    std::vector<sptr<Object>> getCollisionCandidates(const std::vector<sptr<Object>> &worldObjects);

private:
    void resetRays();

protected:
    float m_modelRadius;

    sf::Vector2f m_viewDirection = {1, 0};
    float m_viewDistance;
    float m_viewAngle;
    std::size_t m_viewResolution;

    std::vector<sf::Vector2f> m_viewBoundaryPoints;
};


#endif //SIMPLEGAMEENGINE_PLAYER_H
