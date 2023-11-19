#pragma once

#include <stdint.h>

struct WindowConfig
{
  int   width;
  int   height;
  int   frameRateLimit;
};

struct PlayerConfig
{
  float   shapeRadius;
  float   collisionRadius;
  float   speed;
  uint8_t fillColorRed;
  uint8_t fillColorGreen;
  uint8_t fillColorBlue;
  uint8_t outlineColorRed;
  uint8_t outlineColorGreen;
  uint8_t outlineColorBlue;
  float   outlineThickness;
  int     numOfVertices;
};

struct EnemyConfig
{
  float   shapeRadius;
  float   collisionRadius;
  float   minSpeed;
  float   maxSpeed;
  uint8_t fillColorRed;
  uint8_t fillColorGreen;
  uint8_t fillColorBlue;
  uint8_t outlineColorRed;
  uint8_t outlineColorGreen;
  uint8_t outlineColorBlue;
  float   outlineThickness;
  int     minNumOfVertices;
  int     maxNumOfVertices;
  int     smallLifespan;
  int     spawnInterval;
};

struct BulletConfig
{
  float   shapeRadius;
  float   collisionRadius;
  float   speed;
  uint8_t fillColorRed;
  uint8_t fillColorGreen;
  uint8_t fillColorBlue;
  uint8_t outlineColorRed;
  uint8_t outlineColorGreen;
  uint8_t outlineColorBlue;
  float   outlineThickness;
  int     numOfVertices;
  int     lifespan;
};

class Config
{
public:
  PlayerConfig playerConfig;
  EnemyConfig enemyConfig;
  BulletConfig bulletConfig;
  WindowConfig windowConfig;

  const int numOfConfigVariables = 41;

  void loadConfig();
};

extern Config g_config;
