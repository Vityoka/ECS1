#pragma once

#include "scene.h"
#include <map>
#include <memory>
#include "entity_manager.h"

class ScenePlay : public Scene
{
  struct PlayerConfig
  {
    float X, Y, CX, CY, SPEED, MAXSPEED, JUMP, GRAVITY; 
    std::string WEAPON;
  };

protected:
  std::shared_ptr<Entity> m_player;
  std::string             m_levelPath;
  PlayerConfig            m_playerConfig;
  bool                    m_drawTextures = true;
  bool                    m_drawCollision = false;
  bool                    m_drawGrid = false;
  const Vec2f             m_gridSize = { 64, 64 };
  sf::Text                m_gridText;

public:
  ScenePlay(GameEngine* gameEngine, const std::string& levelPath);
  void init(const std::string & levelPath);

  Vec2f gridtoMidPixel(float gridX, float gridY, std::shared_ptr<Entity> entity);
  void sDoAction(const Action& action);
  void loadLevel(const std::string& filename);
  void spawnPlayer();
  void spawnBullet(std::shared_ptr<Entity> entity);
  void sLifespan();
  void sCollision();
  void sMovement();
  void sAnimation();
  void sRender();
  void onEnd();
  void update();
};