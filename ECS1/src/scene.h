#pragma once

#include <memory>
#include "entity_manager.h"
#include "action.h"

// forward declaration
class GameEngine;

typedef std::map<int, std::string> ActionMap;

class Scene
{
protected:
  GameEngine* m_game = nullptr;
  EntityManager m_entityManager;
  ActionMap m_actionMap;
  bool m_paused = false;
  bool m_hasEnded = false;
  size_t m_currentFrame = 0;
  
  virtual void onEnd() = 0;
  void setPaused(bool paused);

public:
  Scene();
  Scene(GameEngine* gameEngine);
  
  virtual void update() = 0;
  virtual void sDoAction (const Action & action) = 0;
  virtual void sRender() = 0;
  
  virtual void doAction(const Action& action);  //TODO: eredetileg a  =0 nem volt itt szal lehet irni kene vmit ide?
  void simulate(const size_t frames); // going to call the update() of the derived scene a couple times
  void registerAction(int inputKey, const std::string& actionName);
  
  size_t width() const;
  size_t height() const;
  size_t currentFrame() const;
  
  bool hasEnded() const;
  const ActionMap& getActionMap() const;
  void drawLine(const Vec2f& p1, const Vec2f& p2);
};
