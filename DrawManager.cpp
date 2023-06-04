#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
using namespace std;

#include "DrawManager.h"
#include "Env.h"

void DrawManager::draw_snake(sf::RenderWindow *window,
                             deque<pair<int, int>> *snake) {
  sf::RectangleShape body(sf::Vector2f(Env::BLOCK_SIZE, Env::BLOCK_SIZE));
  body.setFillColor(sf::Color(10, 150, 32));
  for (auto position : *snake) {
    body.setPosition(position.first, position.second);
    window->draw(body);
    body.setFillColor(sf::Color::Green);
  }
}
void DrawManager::draw_apple(sf::RenderWindow *window,
                             pair<int, int> *position) {
  sf::RectangleShape apple(sf::Vector2f(Env::BLOCK_SIZE, Env::BLOCK_SIZE));
  apple.setFillColor(sf::Color::Red);
  apple.setPosition(position->first, position->second);
  window->draw(apple);
}

void DrawManager::draw_score(sf::RenderWindow *window, int score) {
  sf::RectangleShape score_board(sf::Vector2f(Env::WIDTH, 40));
  score_board.setPosition(0, Env::HEIGHT);
  score_board.setFillColor(sf::Color::White);
  sf::Text score_text;
  sf::Font font;
  font.loadFromFile("./ARIAL.TTF");
  score_text.setFont(font);
  score_text.setString("Score : " + to_string(score));
  score_text.setFillColor(sf::Color::Black);
  score_text.setCharacterSize(14);
  score_text.setPosition(20, Env::HEIGHT + 10);
  window->draw(score_board);
  window->draw(score_text);
}

void DrawManager::draw_start(sf::RenderWindow *window) {
  sf::Text header, continue_text;
  sf::Font font;
  font.loadFromFile("./ARIAL.TTF");
  header.setFont(font);
  header.setString("Snake Game");
  header.setCharacterSize(24);
  header.setFillColor(sf::Color::White);
  header.setPosition(130, 160);
  continue_text.setFont(font);
  continue_text.setString("Press any key to start");
  continue_text.setCharacterSize(20);
  continue_text.setFillColor(sf::Color::White);
  continue_text.setPosition(90, 200);
  window->draw(header);
  window->draw(continue_text);
}

void DrawManager::draw_gameover(sf::RenderWindow *window) {
  sf::Text gameover_text, continue_text;
  sf::Font font;
  font.loadFromFile("./ARIAL.TTF");
  gameover_text.setFont(font);
  gameover_text.setString("GAME OVER");
  gameover_text.setCharacterSize(24);
  gameover_text.setFillColor(sf::Color::Red);
  gameover_text.setPosition(130, 160);
  continue_text.setFont(font);
  continue_text.setString("Press any key to continue");
  continue_text.setCharacterSize(20);
  continue_text.setFillColor(sf::Color::Red);
  continue_text.setPosition(90, 200);
  window->draw(gameover_text);
  window->draw(continue_text);
}