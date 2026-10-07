#pragma once

#include <vector>

#include "../../objects/circle/circle.hpp"
#include "../spatial/quadtree.hpp"


class CollisionSolver
{
public:

    void solve(
        std::vector<Circle*>& circles,
        const QuadTree& spatialTree
    );

private:

    void resolveCollision(
        Circle& a,
        Circle& b
    );
};

