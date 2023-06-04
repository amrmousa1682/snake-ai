#include "Apple.h"
#include "DrawManager.h"
#include "Env.h"
#include "PathFinder.h"
#include "Snake.h"
#include <SFML/Graphics.hpp>
using namespace std;

class Game {
private:
  sf::RenderWindow window;
  sf::Clock timer;
  Snake snake = Snake(0, 0);
  Apple apple = Apple();
  DrawManager drawManager = DrawManager();
  PathFinder pathFinder = PathFinder();
  int score = 0;

public:
  Game() {
    srand(time(NULL));
    window.create(sf::VideoMode(Env::WIDTH, Env::HEIGHT + 40), "Snake Game");
    start();
  }
  void start() {
    window.clear();
    drawManager.draw_start(&window);
    window.display();
    while (window.isOpen()) {
      sf::Event event;
      while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
          window.close();
        else if (event.type == sf::Event::KeyPressed) {
          this->new_game();
        }
      }
    }
  }
  void new_game() {
    pathFinder.road.clear();
    snake = Snake(0, 0);
    apple.respawn(&snake.body);
    score = 1;
    timer.restart();
    update_screen();
    game_loop();
  }
  void update_screen() {
    window.clear();
    drawManager.draw_snake(&window, &snake.body);
    drawManager.draw_apple(&window, &apple.position);
    drawManager.draw_score(&window, score);
    window.display();
  }
  void game_loop() {
    sf::Event event;
    while (window.isOpen()) {
      while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
          window.close();
      }
      if (timer.getElapsedTime().asSeconds() > 1.0 / Env::FPS) {
        snake.move(pathFinder.find_road(&snake, apple.position));
        if (apple.is_eaten(snake.body.front())) {
          snake.grow();
          apple.respawn(&snake.body);
          score++;
        }
        if (snake.is_dead(snake.body.front()) ||
            score == Env::WIDTH * Env::HEIGHT / Env::BLOCK_SIZE - 1) {
          drawManager.draw_gameover(&window);
          window.display();
          score = 0;
          return;
        }
        update_screen();
        timer.restart();
      }
    }
  }
};
int main() { Game g = Game(); }