cmake_minimum_required(VERSION 3.10)
project(FlappyBirdSFML)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(flappy 
    src/main.cpp
    src/GameManager.cpp
    src/FlappyBird.cpp
    src/Asteroid.cpp
    src/Laser.cpp
)

target_include_directories(flappy PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(flappy sfml-graphics sfml-window sfml-system)
