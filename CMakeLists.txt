cmake_minimum_required(VERSION 3.10)
project(FlappyBirdSFML)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(flappy main.cpp)
target_link_libraries(flappy sfml-graphics sfml-window sfml-system)
