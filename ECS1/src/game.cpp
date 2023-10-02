#include "game.h"

Game::Game(sf::RenderWindow& window) : m_window(window)
{
  init();
}

void Game::init()
{
  // Set game state
  m_gameState = GameState::GAME_RUNNING;

  // Load resources
  //if (!m_soundBufferBallBrickCollision.loadFromFile("./res/audio/explosion.wav"))
  //{
  //  std::cout << "Error loading file audio/explosion.wav\n";
  //}
  //else
  //{
  //  //m_music.play();
  //}

  //Create entities

}

bool Game::isRunning() const
{
  return m_window.isOpen();
}

void Game::pollEvents()
{
  // check all the window's events that were triggered since the last iteration of the loop
  while (m_window.pollEvent(m_event))
  {
    switch(m_event.type)
    {
      // "close requested" event: we close the window
      case sf::Event::Closed:
      {
        m_window.close();
        break;
      }
      case sf::Event::MouseButtonPressed:
      {
        if (m_gameState == GameState::GAME_INIT)
        {
          m_gameState = GameState::GAME_RUNNING;
        }
        break;
      }
    }
  }
}

void Game::render()
{
  //clear window
  m_window.clear(sf::Color::Black);

  //draw onto window
  switch(m_gameState)
  {
    case GameState::GAME_INIT:
    case GameState::GAME_RUNNING:
    {
      // Draw entities
      //for (auto& entity : m_entities)
      //{
      //    m_window.draw(entity->getShape());
      //}
      break;
    }
    case GameState::GAME_OVER:
    {
      break;
    }
  }
  // Display window
  m_window.display();
}

void Game::update()
{
  // Time control. Currently overriden with constant to support debugging.
  //m_deltaTime = m_clock.restart().asSeconds();  
  //std::cout << m_deltaTime << std::endl;
  m_deltaTime = 0.017;  // if real clock is used than in debug mode breakpoint sets infinite time and everything falls apart.

  m_window.clear(sf::Color::Black);
  pollEvents();

  switch(m_gameState)
  {
    case GAME_INIT:
    {
      break;
    }
    case GAME_RUNNING:
    {
      updateNormal();
      break;
    }
    case GAME_OVER:
    {
      break;
    }
  }
}


void Game::updateNormal()
{
  
}
