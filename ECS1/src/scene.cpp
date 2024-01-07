#include "scene.h"
#include "game_engine.h"

Scene::Scene() = default;

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
  return m_game->window().getSize().x;
}

size_t Scene::height() const
{
  return m_game->window().getSize().y;
}

size_t Scene::currentFrame() const
{
  return m_currentFrame;
}

bool Scene::hasEnded() const
{
  return m_hasEnded;
}

void Scene::drawLine(const Vec2f& p1, const Vec2f& p2)
{
  sf::VertexArray line(sf::LinesStrip, 2);

  line[0].position = sf::Vector2f(p1.x, p1.y);
  line[1].position = sf::Vector2f(p2.x, p2.y);

  this->m_game->window().draw(line);
}

void Scene::doAction(const Action& action)
{
  sDoAction(action);
}
