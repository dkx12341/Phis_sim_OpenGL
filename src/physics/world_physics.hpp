#pragma once

#include <vector>

#include <glm/vec2.hpp>

#include "../objects/circle/circle.hpp"


class WorldPhysics
{
public:
    WorldPhysics(
        const glm::vec2& gravity,
        const glm::vec2& minBounds,
        const glm::vec2& maxBounds
    );

    void addCircle(Circle& circle);

    void update(float deltaTime);

private:
    glm::vec2 gravity;

    glm::vec2 minBounds;
    glm::vec2 maxBounds;

    std::vector<Circle*> circles;

    void applyGravity(Circle& circle);

    void handleBounds(Circle& circle);
};