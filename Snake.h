#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
using namespace std;

#ifndef SNAKE_AI_SNAKE_H
#define SNAKE_AI_SNAKE_H

class Snake {

public:
    deque<pair<int, int>> body;
    pair<int, int> head, tail;
    int direction;

    Snake(int x, int y);
    void move();
    void grow();
    void follow_road(deque<int>*road);
    bool is_dead(pair<int,int> head);
};


#endif //SNAKE_AI_SNAKE_H
