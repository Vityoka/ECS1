#include "scene_menu.h"
#include "scene_play.h"
#include "game_engine.h"

SceneMenu::SceneMenu(GameEngine* gameEngine) 
: Scene(gameEngine)
{
  init();
}

void SceneMenu::init()
{
  m_selectedMenuIndex = 0;

  registerAction(sf::Keyboard::Down, "DOWN");
  registerAction(sf::Keyboard::Up, "UP");
  registerAction(sf::Keyboard::Enter, "PLAY");
  registerAction(sf::Keyboard::Escape, "QUIT");

  m_title = "COMP4300 Assignment 3 - Mario";

  m_menuStrings.emplace_back("Level 1");
  m_menuStrings.emplace_back("Level 2");
  m_menuStrings.emplace_back("Level 3");

  m_levelPaths.emplace_back("./src/level1.txt");
  m_levelPaths.emplace_back("./src/level2.txt");
  m_levelPaths.emplace_back("./src/level3.txt");

  m_menuText.setFont(m_game->assets().getFont("Tech"));
}

void SceneMenu::update()
{
  sRender();
  if (m_hasEnded)
  {
    m_game->quit();
  }
}

void SceneMenu::onEnd()
{
  // If the menu scene ends, initiate quit from game
  m_hasEnded = true;
}

void SceneMenu::sRender()
{
  m_game->window().clear(sf::Color(100, 27, 0));

  // drawing the game title in the top-left of the screen
  m_menuText.setString(m_title);
  m_menuText.setCharacterSize(32);
  m_menuText.setFillColor(sf::Color::Black);
  m_menuText.setPosition(sf::Vector2f(m_game->window().getSize().x / 2 - m_menuText.getCharacterSize() * 3, 10));
  m_game->window().draw(m_menuText);

  // draw all the menu options
  for (size_t i = 0; i < m_menuStrings.size(); i++) {
    m_menuText.setString(m_menuStrings.at(i));
    m_menuText.setFillColor(i == m_selectedMenuIndex ? sf::Color::White : sf::Color::Black);
    m_menuText.setPosition(sf::Vector2f(m_game->window().getSize().x / 2 - m_menuText.getCharacterSize() * 2, 250 + i * 72));
    m_game->window().draw(m_menuText);
  }

  m_menuText.setString(
      "Left :  A        S :  Down        Up : W        D : Do");
  m_menuText.setFillColor(sf::Color::Black);
  m_menuText.setCharacterSize(12);
  m_menuText.setPosition( sf::Vector2f(m_menuText.getCharacterSize(), height() - m_menuText.getCharacterSize() * 2));
  m_game->window().draw(m_menuText);

  m_game->window().display();
}

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
    std::cout << "Selected menuIndex is: " << m_selectedMenuIndex << " ,which is the string: " << m_menuStrings[m_selectedMenuIndex] << std::endl;
  }
}