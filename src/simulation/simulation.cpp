#include "simulation.hpp"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <cstdlib>
#include <cstdio>
#include <ctime>


Simulation::Simulation()
    : worldPhysics(
        glm::vec2(0.0f, 0.0f),
        glm::vec2(-60.0f, -60.0f),
        glm::vec2(60.0f, 60.0f)
    )
{
  srand(static_cast<unsigned int>(time(nullptr)));

    glm::vec2 worldSize = Simulation::worldPhysics.getMaxBounds();
    for (int i = 0; i < 300; ++i)
    {
        auto circle =
            std::make_unique<Circle>(
                0.5f,
                0.7f,
                0.9f
            );

        circle->setVelocity(
            glm::vec2(
                static_cast<float>((rand() % 400 - 200)/10),
                static_cast<float>((rand() % 400 - 200)/10)
            )
        );

        circle->setPosition(
            glm::vec2(
                static_cast<float>(rand() % static_cast<int>(worldSize.x))
                    - worldSize.x / 2.0f,

                static_cast<float>(rand() % static_cast<int>(worldSize.y))
                    - worldSize.y / 2.0f
            )
        );

        worldPhysics.addCircle(*circle);

        circles.push_back(
            std::move(circle)
        );
    }
}


void Simulation::update(float deltaTime)
{
    worldPhysics.update(deltaTime);
}


const std::vector<std::unique_ptr<Circle>>&
Simulation::getCircles() const
{
    return circles;
}