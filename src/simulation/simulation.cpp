#include "simulation.hpp"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <cstdlib>
#include <cstdio>
#include <ctime>


Simulation::Simulation()
    : playerShip(
        10.0f,  // masa
        2.0f,   // rozmiar wizualny
        1.2f,   // promień hitboxa
        0.5f    // restytucja
    ),
      worldPhysics(
          glm::vec2(0.0f, 0.0f),
          glm::vec2(-60.0f, -60.0f),
          glm::vec2(60.0f, 60.0f)
      )
{
    playerShip.setPosition(glm::vec2(0.0f, 0.0f));


    srand(static_cast<unsigned int>(time(nullptr)));

    glm::vec2 worldSize = Simulation::worldPhysics.getMaxBounds();
    for (int i = 0; i < 100; ++i)
    {
        auto circle =
            std::make_unique<Circle>(
                1.0f,
                1.0f,
                0.9f
            );

        circle->setVelocity(
            glm::vec2(
                static_cast<float>((rand() % 100 - 50)/10),
                static_cast<float>((rand() % 100 - 50)/10)
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
    worldPhysics.update(deltaTime, playerShip);
}

Ship& Simulation::getPlayerShip()
{
    return playerShip;
}

const Ship& Simulation::getPlayerShip() const
{
    return playerShip;
}


const std::vector<std::unique_ptr<Circle>>&
Simulation::getCircles() const
{
    return circles;
}