#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

#include "Snake.h"

using namespace std;

#ifndef SNAKE_AI_PATHFINDER_H
#define SNAKE_AI_PATHFINDER_H


class PathFinder {
public:
    deque<int> road;
    int find_road(Snake *snake,pair<int, int> apple);
private:
    deque<int> bfs( Snake *snake, pair<int,int> target);
    bool check_valid_road(Snake *snake,deque<int> *road,bool grow);
    int find_safe_move( Snake *snake,pair<int,int> apple);
};


#endif //SNAKE_AI_PATHFINDER_H
