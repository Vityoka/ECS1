#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "game.h"

int main()
{
  // create window and game
  sf::RenderWindow window(sf::VideoMode(800, 600), "ECS1");
  window.setFramerateLimit(60);

  Game game(window);

  while (game.isRunning())
  {
    game.update();
    game.render();
  }

  int a;
  std::cin >> a;

  return 0;
}