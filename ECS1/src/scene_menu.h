#pragma once

#include "scene.h"
#include <string>
#include <memory>
#include <vector>
#include "entity_manager.h"

class SceneMenu: public Scene
{
protected:
  std::string              m_title;
  std::vector<std::string> m_menuStrings; 
  std::vector<std::string> m_levelPaths;
  sf::Text                 m_menuText;
  size_t                   m_selectedMenuIndex = 0;

  void init();
  void update();
  void onEnd();
  void sDoAction (const Action& action);

public:
  SceneMenu(GameEngine* gameEngine = nullptr);
  void sRender();

  //...
};