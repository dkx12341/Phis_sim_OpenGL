#pragma once

#include <memory>
#include <vector>

#include "objects/circle/circle.hpp"
#include "physics/world_physics.hpp"


class Simulation
{
public:

    Simulation();

    void update(float deltaTime);

    const std::vector<std::unique_ptr<Circle>>&
    getCircles() const;


private:

    WorldPhysics worldPhysics;

    std::vector<std::unique_ptr<Circle>> circles;
};