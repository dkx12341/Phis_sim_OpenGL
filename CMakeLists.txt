cmake_minimum_required(VERSION 3.25)

project(PhysicsSimulation
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

add_executable(PhysicsSimulation
    src/main.cpp

    src/simulation/objects/circle/circle.cpp
    src/simulation/objects/circle/circle.hpp

    src/renderer/shader.cpp
    src/renderer/shader.hpp

    src/renderer/circle_renderer.cpp
    src/renderer/circle_renderer.hpp

    src/simulation/physics/world_physics.hpp
    src/simulation/physics/world_physics.cpp

    src/camera/camera.hpp
    src/camera/camera.cpp

    src/simulation/simulation.hpp
    src/simulation/simulation.cpp
    ) 

target_link_libraries(PhysicsSimulation
    PRIVATE
        glfw
        glm::glm
        glad::glad
)

add_custom_command(TARGET PhysicsSimulation POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/src/shaders"
        "$<TARGET_FILE_DIR:PhysicsSimulation>/shaders"
)