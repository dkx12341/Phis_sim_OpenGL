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

add_executable(PhysicsSimulation
    src/main.cpp
)

target_link_libraries(PhysicsSimulation
    PRIVATE
        glfw
        glm::glm
)
