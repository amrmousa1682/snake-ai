#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
using namespace std;

#ifndef SNAKE_AI_DRAWMANAGER_H
#define SNAKE_AI_DRAWMANAGER_H

class DrawManager {
public:
  void draw_snake(sf::RenderWindow *window, deque<pair<int, int>> *snake);
  void draw_apple(sf::RenderWindow *window, pair<int, int> *apple);
  void draw_score(sf::RenderWindow *window, int score);
  void draw_gameover(sf::RenderWindow *window);
  void draw_start(sf::RenderWindow *window);
};

#endif
