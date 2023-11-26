#include "scene_menu.h"
#include "scene_play.h"
#include "game_engine.h"

SceneMenu::SceneMenu(GameEngine* gameEngine)
{
  m_game = gameEngine;
}

void SceneMenu::init(){}
void SceneMenu::update(){}
void SceneMenu::onEnd(){}
void SceneMenu::sRender(){}


void SceneMenu::sDoAction (const Action& action)
{
  if (action.type() == "START")
  {
    if (action.name() == "UP")
    {
      if (m_selectedMenuIndex > 0) { m_selectedMenuIndex--; }
      else { m_selectedMenuIndex = m_menuStrings.size() - 1; }
    }
    else if (action.name() == "DOWN")
    {
      m_selectedMenuIndex = (m_selectedMenuIndex + 1) % m_menuStrings.size();
    }
    else if (action.name() == "PLAY")
    {
      m_game->changeScene("PLAY", std::make_shared<ScenePlay>(m_game, m_levelPaths[m_selectedMenuIndex]));
    }
    else if (action.name() == "QUIT")
    {
      onEnd();
    }
  }
}