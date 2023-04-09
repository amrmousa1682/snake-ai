#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

#include "PathFinder.h"
#include "Env.h"
#include "DrawManager.h"
using namespace std;

int PathFinder::find_road(Snake *snake, pair<int, int> apple) {
    //bfs from head to apple
    if(!road.empty()){
        int ans=road.front();
        road.pop_front();
        return ans;
    }
    road=bfs(snake,apple);
    //check if road is safe
    if(!road.empty()){
        road.pop_front();
        if(!check_valid_road(snake,&road,1)){
            road.clear();//not safe
        }
    }
    //if not safe find safe move
    if(road.empty()){
        return find_safe_move(snake,apple);
    }
    int ans=road.front();
    road.pop_front();
    return ans;
}
bool PathFinder::check_valid_road(Snake *snake,deque<int> *road,bool grow){
    Snake virtual_snake(*snake);
    virtual_snake.follow_road(road);
    if(grow)
    virtual_snake.grow();
    return !bfs(&virtual_snake,virtual_snake.tail).empty();
}
deque<int> PathFinder::bfs(Snake *snake, pair<int, int> target) {
    queue<tuple<int,int,int>> q;
    map<tuple<int,int,int>,bool> vis;
    map<tuple<int,int,int>,tuple<int,int,int>> par;
    q.push({snake->head.first,snake->head.second,snake->direction});
    par[q.front()]={-1,-1,-1};
    vis[{snake->head.first,snake->head.second,snake->direction}]=1;
    while (!q.empty()){
        int x,y,d;
        tie(x,y,d)=q.front();
        q.pop();
        if(x==target.first&&y==target.second){
            deque<int> road;
            while (d!=-1){
                road.push_front(d);
                tie(x,y,d)=par[{x,y,d}];
            }
            if(!snake->is_dead(target)||road.size()>2)
            return road;
        }
        if(snake->is_dead({x, y})&&get<0>(par[{x,y,d}])!=-1)
            continue;
        for(int i=0;i<4;i++){
            if((d==0&&i==1)||(d==1&&i==0)||(d==2&&i==3)||(d==3&&i==2))
                continue;
            switch (i)
            {
                case 0:
                    if(vis[{x+Env::BLOCK_SIZE,y,i}])
                        continue;
                    vis[{x+Env::BLOCK_SIZE,y,i}]=1;
                    par[{x+Env::BLOCK_SIZE,y,i}]={x,y,d};
                    q.push({x+Env::BLOCK_SIZE,y,i});
                    break;
                case 1:
                    if(vis[{x-Env::BLOCK_SIZE,y,i}])
                        continue;
                    vis[{x-Env::BLOCK_SIZE,y,i}]=1;
                    par[{x-Env::BLOCK_SIZE,y,i}]={x,y,d};
                    q.push({x-Env::BLOCK_SIZE,y,i});
                    break;
                case 2:
                    if(vis[{x,y+Env::BLOCK_SIZE,i}])
                        continue;
                    vis[{x,y+Env::BLOCK_SIZE,i}]=1;
                    par[{x,y +Env::BLOCK_SIZE,i}]={x,y,d};
                    q.push({x,y +Env::BLOCK_SIZE,i});
                    break;
                case 3:
                    if(vis[{x,y-Env::BLOCK_SIZE,i}])
                        continue;
                    vis[{x,y-Env::BLOCK_SIZE,i}]=1;
                    par[{x,y -Env::BLOCK_SIZE,i}]={x,y,d};
                    q.push({x,y - Env::BLOCK_SIZE,i});
                    break;
            }
        }
    }
    return {};
}
int PathFinder::find_safe_move(Snake *snake,pair<int,int> apple) {

    int d=snake->direction,x=snake->head.first,y=snake->head.second;
    deque<int>temp;
    deque<pair<int,int>>ans;
    for(int i=0;i<4;i++){
        if((d==0&&i==1)||(d==1&&i==0)||(d==2&&i==3)||(d==3&&i==2))
            continue;
        pair<pair<int,int>,int>new_head;
        switch (i)
        {
            case 0:
                new_head={{x + Env::BLOCK_SIZE, y},i};
                break;
            case 1:
                new_head={{x - Env::BLOCK_SIZE, y},i};
                break;
            case 2:
                new_head={{x , y+ Env::BLOCK_SIZE},i};
                break;
            case 3:
                new_head={{x , y- Env::BLOCK_SIZE},i};
                break;
        }
        if(snake->is_dead(new_head.first))
            continue;
        temp.push_back(i);
        if(check_valid_road(snake,&temp,new_head.first==apple)){
            ans.push_back({abs(new_head.first.first-snake->tail.first+new_head.first.second-snake->tail.second),i});
        }
        temp.pop_back();
    }
    sort(ans.begin(),ans.end());
    return (!ans.empty())?ans.back().second:0;
}