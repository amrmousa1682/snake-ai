# SFML Snake Game with AI

## SFML Snake Game with AI Using BFS To Find The Best Way To Apple

This is a simple game of Snake with an AI component written in C++ using the SFML library. The AI component uses a BFS algorithm to find the shortest path to the apple and then checks if this path is safe. If the path is safe after eating the apple, the AI will take this path. Otherwise, it will take any available safe move.

## Project Run

![ezgif-3-6444a3ed1f](https://github.com/amrmousa1682/snake-ai/assets/70464867/5a1d5814-1ef8-47d8-9c55-ffa8ba20db9d)

## Requirements

- CMake version 3.24 or newer
- SFML 2.5 library with the graphics and audio components

## Installation and Setup

1. Clone the repository to your local machine.
2. Install CMake and SFML on your machine if they are not already installed. You can download CMake from [cmake.org](https://cmake.org/download/) and SFML from [sfml-dev.org](https://www.sfml-dev.org/download.php).
3. Open a terminal and navigate to the project folder.
4. Run the command `cmake build ./` to generate the build files.
5. Run the command `make` to build the executable.
6. Run the executable with the command `./Snake_AI`.

## Usage

When you run the executable, the game will start automatically. The AI component will automatically navigate the snake towards the apple and try to get the highest score possible.

## Project Structure

- `main.cpp`: The main entry point of the program.
- `Snake.cpp` and `Snake.h`: The implementation and header files for the Snake class, which represents the snake in the game.
- `Env.h`: The header file for the Environment class, which manages the game environment.
- `Apple.cpp` and `Apple.h`: The implementation and header files for the Apple class, which represents the food that the snake eats.
- `DrawManager.cpp` and `DrawManager.h`: The implementation and header files for the DrawManager class, which manages the drawing of the game objects.
- `PathFinder.cpp` and `PathFinder.h`: The implementation and header files for the PathFinder class, which implements the BFS algorithm used by the AI to find the shortest path to the apple.

## Conclusion

This Snake AI game provides an entertaining way to experience the power of AI in action.The code is well-structured and easy to read, making it a good starting point for anyone interested in learning about game programming or AI. Give it a try and see how it work.
