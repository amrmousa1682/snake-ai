cmake_minimum_required(VERSION 3.24)
project(Snake_Ai)

set(CMAKE_CXX_STANDARD 17)
find_package(SFML 2.5 COMPONENTS graphics audio)

add_executable(Snake_AI main.cpp Snake.cpp Snake.h Env.h Apple.cpp Apple.h DrawManager.cpp DrawManager.h PathFinder.cpp PathFinder.h)

target_link_libraries(Snake_AI sfml-graphics sfml-audio)
