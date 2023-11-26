#include "game_engine.h"
#include "scene_menu.h"
#include "scene_play.h"
#include "action.h"

GameEngine::GameEngine(const std::string& path)
{
  init(path);
}

void GameEngine::init(const std::string& path)
{
  m_assets.loadfromFile(path); // It was not like this in the asset class arch

  m_window.create(sf::VideoMode(1280, 768), "COMP4300 Assignment3");
  m_window.setFramerateLimit(60);

  changeScene("MENU", std::make_shared<SceneMenu>(this)); //TODO: just to understand, why "this" is neeed?
}

void GameEngine::update()
{
  //main loop
  sUserInput();
  currentScene()->update();
}

void GameEngine::run()
{
  while (isRunning())
  {
    update();
  }
}

void GameEngine::quit()
{
  //quit game

}

bool GameEngine::isRunning()
{
  return m_running & m_window.isOpen();
}

Assets& GameEngine::assets()
{
  return m_assets;
}

std::shared_ptr<Scene> GameEngine::currentScene()
{
  return m_sceneMap[m_currentScene];
}

sf::RenderWindow& GameEngine::window()
{
  return m_window;
}

void GameEngine::changeScene(const std::string& sceneName, std::shared_ptr<Scene> scene, bool endCurrentScene)
{
  if (endCurrentScene)
  {
    m_sceneMap.erase(m_currentScene);
  }
  m_sceneMap[sceneName] = scene;
  m_currentScene = sceneName;
}

void GameEngine::sUserInput()
{
  sf::Event event;
  while (m_window.pollEvent (event))
  {
    if (event.type == sf::Event::Closed)
    {
      quit();
    }
    if (event.type == sf::Event::KeyPressed)
    {
      if (event.key.code == sf::Keyboard::X)
      {
        std::cout << "screenshot saved to " << "test.png" << std::endl; 
        sf::Texture texture;
        texture.create(m_window.getSize().x, m_window.getSize().y);
        texture.update(m_window);
        if (texture.copyToImage().saveToFile("test.png"))
        {
          std::cout << "screenshot saved to "<< "test.png" << std::endl;
        }
      }
    }
    if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
    {
      // if the current scene does not have an action associated with this key, skip the event
      if (currentScene()->getActionMap().find(event.key.code) == currentScene()->getActionMap().end()) 
        { continue; }
      
      // determine start or end action by whether it was key press or release
      const std::string actionType = (event.type == sf::Event::KeyPressed) ? "START" : "END";
      // look up the action and send the action to the scene
      currentScene()->doAction(Action(currentScene()->getActionMap().at(event.key.code), actionType));
    }
  }
}