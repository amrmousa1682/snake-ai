#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
using namespace std;

#ifndef SNAKE_AI_APPLE_H
#define SNAKE_AI_APPLE_H


class Apple {
public:
    pair<int, int> position;
    void respawn(deque<pair<int, int>> *snake);
    bool is_eaten(pair<int, int> head);
};


#endif //SNAKE_AI_APPLE_H
