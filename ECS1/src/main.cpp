#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "game_engine.h"
#include "entity.h"

int main()
{
  GameEngine game("./config.txt");
  game.run();

  return 0;
}