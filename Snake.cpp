#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

#include "Snake.h"
#include "Env.h"

using namespace std;

Snake::Snake(int x, int y) {
    body.push_back({x, y});
    head = {x, y};
    tail = head;
    direction=0;
}


void Snake::move() {
    switch (direction)
    {
        case 0:
            head.first += Env::BLOCK_SIZE;
            break;
        case 1:
            head.first -= Env::BLOCK_SIZE;
            break;
        case 2:
            head.second += Env::BLOCK_SIZE;
            break;
        case 3:
            head.second -= Env::BLOCK_SIZE;
            break;
    }
    body.push_front(head);
    body.pop_back();
    tail = body.back();
    this->direction = direction;
}

void Snake::follow_road(deque<int> *road) {
    for(auto dir:*road){
        this->direction=dir;
        this->move();
    }
}
void Snake::grow() {
    body.push_back(tail);
}
bool Snake::is_dead(pair<int,int> head) {
    if (head.first < 0 || head.first >= Env::WIDTH || head.second < 0 || head.second >= Env::HEIGHT)
        return true;
    for (auto i = body.begin() +1; i < body.end()-1; i++)
        if (head == *i)
            return true;
    return false;
}