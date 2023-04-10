#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Apple.h"
#include "Env.h"
#include "DrawManager.h"
#include "PathFinder.h"
using namespace std;

class Game
{
private:
    sf::RenderWindow window;
    sf::Clock timer;
    Snake snake = Snake(0, 0);
    Apple apple = Apple();
    DrawManager drawManager=DrawManager();
    PathFinder pathFinder=PathFinder();
    int score=0;

public:
    Game()
    {
        window.create(sf::VideoMode(Env::WIDTH, Env::HEIGHT+40), "Snake Game");
        start();
    }
    void start(){
        window.clear();
        drawManager.draw_start(&window);
        window.display();
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                else if(event.type == sf::Event::KeyPressed) {
                    this->new_game();
                }
            }
        }
    }
    void update_screen(){
        window.clear();
        drawManager.draw_snake(&window,&snake.body);
        drawManager.draw_apple(&window,&apple.position);
        drawManager.draw_score(&window,score);
        window.display();
    }
    void new_game()
    {
        pathFinder.road.clear();
        snake = Snake(0, 0);
        apple.respawn(&snake.body);
        score=1;
        timer.restart();
        update_screen();
        game_loop();
    }
    void game_loop(){
        sf::Event event;
        while (window.isOpen())
        {
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            if (timer.getElapsedTime().asSeconds() > 1.0 / Env::FPS)
            {
                snake.direction=pathFinder.find_road(&snake,apple.position);
                snake.move();
                if (apple.is_eaten(snake.head))
                {
                    snake.grow();
                    apple.respawn(&snake.body);
                    score++;
                }
                if (snake.is_dead(snake.head)||score==Env::WIDTH*Env::HEIGHT/Env::BLOCK_SIZE-1)
                {
                    drawManager.draw_gameover(&window);
                    window.display();
                    score=0;
                    return;
                }
                update_screen();
                timer.restart();
            }
        }
    }
};
int main()
{
    Game g = Game();
}