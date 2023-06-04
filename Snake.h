#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
using namespace std;

#ifndef SNAKE_AI_SNAKE_H
#define SNAKE_AI_SNAKE_H

class Snake {

public:
  deque<pair<int, int>> body;
  int direction;

  Snake(int x, int y);
  void move(int dir);
  void grow();
  void follow_road(deque<int> *road);
  int get_postion_index(pair<int, int> position);
  bool is_dead(pair<int, int> head);
};

#endif // SNAKE_AI_SNAKE_H
