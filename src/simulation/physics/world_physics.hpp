#pragma once

#include <vector>

#include <glm/vec2.hpp>

#include "../objects/circle/circle.hpp"
#include "spatial/quadtree.hpp"

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

    glm::vec2 getMaxBounds() const;

private:
    glm::vec2 gravity;

    glm::vec2 minBounds;
    glm::vec2 maxBounds;

    std::vector<Circle*> circles;

    QuadTree spatialTree;

    void applyGravity(Circle& circle);

    void handleBounds(Circle& circle);
};