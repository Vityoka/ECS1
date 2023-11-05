#ifndef GAME_H_GUARD
#define GAME_H_GUARD

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "entity_manager.h"
#include <memory>

enum GameState : char{
  GAME_INIT = 0,
  GAME_RUNNING = 1,
  GAME_OVER = 2
};

class Game
{
public:
  Game();

  void run();

private:
  void init();
  void spawnPlayer();
  void spawnEnemy();
  void spawnBullet(const Vec2f& target);

  // Systems
  void sUserInput();
  void sRender();
  void sMovement();
  void sCollision();
  void sEnemySpawner();

  uint64_t m_currentFrame;

  sf::RenderWindow m_window;

  sf::Clock m_clock;
  float m_deltaTime;

  sf::SoundBuffer m_soundBufferBallBrickCollision;
  sf::SoundBuffer m_soundBufferBallPlayerCollision;
  sf::Sound m_sound;
  sf::Music m_music;
  sf::Text m_textGameOver;
  sf::Font m_font;

  EntityManager m_entityManager;
  std::shared_ptr<Entity> m_player;

  GameState m_gameState;

  bool m_paused = false;
};

#endif //GAME_H_GUARD