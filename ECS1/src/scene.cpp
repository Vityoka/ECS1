#include "scene.h"

Scene::Scene()
{

}

Scene::Scene(GameEngine* gameEngine)
{
  m_game = gameEngine;
}

void Scene::registerAction(int inputKey, const std::string& actionName)
{
  m_actionMap[inputKey] = actionName;
}

const ActionMap& Scene::getActionMap() const
{
  return m_actionMap;
}

void Scene::setPaused(bool paused)
{
  m_paused = paused;
}

void Scene::simulate(const size_t frames)
{
  
}
size_t Scene::width() const
{
  return 1; //???
}

size_t Scene::height() const
{
  return 1; //???
}

size_t Scene::currentFrame() const
{
  return 1; //???
}

bool Scene::hasEnded() const
{
  return false; //???
}

void Scene::drawLine(const Vec2f& p1, const Vec2f& p2)
{
  
}

void Scene::doAction(const Action& action)
{

}
