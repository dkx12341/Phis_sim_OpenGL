#pragma once

#include <vector>

#include <glm/vec2.hpp>

#include "../objects/circle/circle.hpp"
#include "../objects/ship/ship.hpp"
#include "spatial/quadtree.hpp"
#include "collision/collision_solver.hpp"

class WorldPhysics
{
public:
    WorldPhysics(
        const glm::vec2& gravity,
        const glm::vec2& minBounds,
        const glm::vec2& maxBounds
    );

    void addCircle(Circle& circle);

    void update(
        float deltaTime,
        Ship& ship
    );

    glm::vec2 getMaxBounds() const;

private:
    glm::vec2 gravity;
    glm::vec2 minBounds;
    glm::vec2 maxBounds;

    std::vector<Circle*> circles;

    QuadTree spatialTree;
    CollisionSolver collisionSolver;

    void applyGravity(Circle& circle);
    void applyGravity(Ship& ship);

    void handleBounds(Circle& circle);
    void handleBounds(Ship& ship);
};