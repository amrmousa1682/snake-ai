#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

#include "Apple.h"
#include "Env.h"

using namespace std;

void Apple::respawn(deque<pair<int, int>> *snake) {
  set<pair<int, int>> s;
  for (int i = 0; i < Env::WIDTH; i += Env::BLOCK_SIZE)
    for (int j = 0; j < Env::HEIGHT; j += Env::BLOCK_SIZE)
      s.insert({i, j});
  for (auto i : *snake)
    s.erase(i);
  int x = rand() % s.size();
  auto it = s.begin();
  while (x--)
    it++;
  position = *it;
}

bool Apple::is_eaten(pair<int, int> head) { return head == position; }