#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

#include "Env.h"
#include "Snake.h"

using namespace std;

Snake::Snake(int x, int y) {
  body.push_back({x, y});
  direction = 0;
}

void Snake::move(int dir) {
  pair<int, int> head = body.front();
  if (dir == 0)
    head.first += Env::BLOCK_SIZE;
  else if (dir == 1)
    head.first -= Env::BLOCK_SIZE;
  else if (dir == 2)
    head.second += Env::BLOCK_SIZE;
  else if (dir == 3)
    head.second -= Env::BLOCK_SIZE;
  body.push_front(head);
  body.pop_back();
  this->direction = dir;
}
int Snake::get_postion_index(pair<int, int> position) {
  int index = 0;
  for (int i = body.size() - 1; i >= 0; i--) {
    if (position == body[i])
      return index;
    index++;
  }
  return -1;
}

void Snake::follow_road(deque<int> *road) {
  for (auto dir : *road) {
    move(dir);
  }
}
void Snake::grow() { body.push_back(body.back()); }

bool Snake::is_dead(pair<int, int> head) {
  if (head.first < 0 || head.first >= Env::WIDTH || head.second < 0 ||
      head.second >= Env::HEIGHT)
    return true;
  for (auto i = body.begin() + 1; i < body.end() - 1; i++)
    if (head == *i)
      return true;
  return false;
}