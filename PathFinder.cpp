#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

#include "DrawManager.h"
#include "Env.h"
#include "PathFinder.h"
using namespace std;

int PathFinder::find_road(Snake *snake, pair<int, int> apple) {
  // check if road is already calculated
  if (!road.empty()) {
    int dir = road.front();
    road.pop_front();
    return dir;
  }
  // find road
  road = bfs(snake, apple);
  // if there is no road find safe move
  if (road.empty()) {
    return find_safe_move(snake, apple);
  }
  road.pop_front();
  if (!check_valid_road(snake, &road, 1)) {
    road.clear();
    return find_safe_move(snake, apple);
  }
  int dir = road.front();
  road.pop_front();
  return dir;
}
deque<int> PathFinder::bfs(Snake *snake, pair<int, int> target) {
  pair<int, int> head = snake->body.front();
  queue<tuple<int, int, int, int>> q; // x,y,direction,number of steps
  map<tuple<int, int>, bool> vis;
  map<tuple<int, int, int>, tuple<int, int, int>> par;
  q.push({head.first, head.second, snake->direction, 0});
  par[{head.first, head.second, snake->direction}] = {-1, -1, -1};
  vis[{head.first, head.second}] = 1;
  while (!q.empty()) {
    int x, y, d, s;
    tie(x, y, d, s) = q.front();
    q.pop();
    if (x == target.first && y == target.second) {
      deque<int> road;
      while (d != -1) {
        road.push_front(d);
        tie(x, y, d) = par[{x, y, d}];
      }
      return road;
    }
    for (int i = 0; i < 4; i++) {
      if ((d == 0 && i == 1) || (d == 1 && i == 0) || (d == 2 && i == 3) ||
          (d == 3 && i == 2))
        continue;
      pair<pair<int, int>, int> new_head;
      switch (i) {
      case 0:
        new_head = {{x + Env::BLOCK_SIZE, y}, i};
        break;
      case 1:
        new_head = {{x - Env::BLOCK_SIZE, y}, i};
        break;
      case 2:
        new_head = {{x, y + Env::BLOCK_SIZE}, i};
        break;
      case 3:
        new_head = {{x, y - Env::BLOCK_SIZE}, i};
        break;
      }
      if (vis[{new_head.first.first, new_head.first.second}])
        continue;
      if (snake->is_dead(new_head.first)) {
        int index = snake->get_postion_index(new_head.first);
        if (s <= index || index == -1)
          continue;
      }
      vis[{new_head.first.first, new_head.first.second}] = 1;
      par[{new_head.first.first, new_head.first.second, i}] = {x, y, d};
      q.push({new_head.first.first, new_head.first.second, i, s + 1});
    }
  }
  return deque<int>();
}

bool PathFinder::check_valid_road(Snake *snake, deque<int> *road, bool grow) {
  Snake virtual_snake(*snake);
  virtual_snake.follow_road(road);
  if (grow)
    virtual_snake.grow();
  return !bfs(&virtual_snake, virtual_snake.body.back()).empty();
}

int PathFinder::find_safe_move(Snake *snake, pair<int, int> apple) {

  int d = snake->direction, x = snake->body.front().first,
      y = snake->body.front().second;
  deque<int> temp;
  deque<pair<int, int>> ans;
  for (int i = 0; i < 4; i++) {
    if ((d == 0 && i == 1) || (d == 1 && i == 0) || (d == 2 && i == 3) ||
        (d == 3 && i == 2))
      continue;
    pair<pair<int, int>, int> new_head;
    switch (i) {
    case 0:
      new_head = {{x + Env::BLOCK_SIZE, y}, i};
      break;
    case 1:
      new_head = {{x - Env::BLOCK_SIZE, y}, i};
      break;
    case 2:
      new_head = {{x, y + Env::BLOCK_SIZE}, i};
      break;
    case 3:
      new_head = {{x, y - Env::BLOCK_SIZE}, i};
      break;
    }
    if (snake->is_dead(new_head.first))
      continue;
    temp.push_back(i);
    if (check_valid_road(snake, &temp, new_head.first == apple)) {
      ans.push_back({abs(new_head.first.first - snake->body.back().first +
                         new_head.first.second - snake->body.back().second),
                     i});
    }
    if(new_head.first == apple)
      ans.push_back({0, i});
    else
      ans.push_back({-1, i});
    temp.pop_back();
  }
  sort(ans.begin(), ans.end());
  return (!ans.empty()) ? ans.back().second : 0;
}