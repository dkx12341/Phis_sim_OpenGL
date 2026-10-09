#pragma once

#include <vector>

#include "../../objects/circle/circle.hpp"
#include "../../objects/ship/ship.hpp"
#include "../spatial/quadtree.hpp"

class CollisionSolver
{
public:
    void solve(
        std::vector<Circle*>& circles,
        const QuadTree& spatialTree,
        Ship& ship
    );

private:
    void resolveCollision(
        Circle& a,
        Circle& b
    );

    void resolveCollision(
        Ship& ship,
        Circle& circle
    );
};