#include "game.h"
#include "vec2f.h"
#include <iostream>

Game::Game() 
{
  init();
}

void Game::init()
{
  // Create game window
  m_window.create(sf::VideoMode(800, 600), "ECS1");
  m_window.setFramerateLimit(60);

  // Time control. Currently overriden with constant to support debugging.
  //m_deltaTime = m_clock.restart().asSeconds();  
  //std::cout << m_deltaTime << std::endl;
  m_deltaTime = 0.017F;  // if real clock is used than in debug mode breakpoint sets infinite time and everything falls apart.

  // Set game state
  m_gameState = GameState::GAME_RUNNING;

  m_player = m_entityManager.addEntity("player");
  std::shared_ptr<CShape> playerShape = std::make_shared<CShape>(3, 10, sf::Color::Blue);
  m_player->cShape = playerShape;
  std::shared_ptr<CInput> playerInput = std::make_shared<CInput>();
  m_player->cInput = playerInput;
  Vec2f pos (100, 100);
  Vec2f velocity (0, 0);
  std::shared_ptr<CTransform> playerTransform = std::make_shared<CTransform>(pos, velocity, 0.0F);
  m_player->cTransform = playerTransform;

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

void Game::run()
{
  while(m_window.isOpen())
  {
    sUserInput();
    sTransform();
    sRender();
    
    m_entityManager.update();
  }
}

void Game::sUserInput()
{
  sf::Event event;

  // check all the window's events that were triggered since the last iteration of the loop
  while (m_window.pollEvent(event))
  {
    switch(event.type)
    {
      // "close requested" event: we close the window
      case sf::Event::Closed:
      {
        m_window.close();
        break;
      }
      // Mouse click event
      case sf::Event::MouseButtonPressed:
      {
        if (m_gameState == GameState::GAME_INIT)
        {
          m_gameState = GameState::GAME_RUNNING;
        }
        break;
      }
      // Keyboard pressed event
      case sf::Event::KeyPressed:
      {
        //std::cout << event.key.code << std::endl; // log message
        if (m_player->cInput) // Check whether the entity has the cInput component available
        {
          if (event.key.code == sf::Keyboard::Key::Down) m_player->cInput->down = true;
          if (event.key.code == sf::Keyboard::Key::Up) m_player->cInput->up = true;
          if (event.key.code == sf::Keyboard::Key::Left) m_player->cInput->left = true;
          if (event.key.code == sf::Keyboard::Key::Right) m_player->cInput->right = true;
        }
        break;
      }
      case sf::Event::KeyReleased:
      {
        //std::cout << event.key.code << std::endl; // log message
        if (m_player->cInput) // Check whether the entity has the cInput component available
        {
          if (event.key.code == sf::Keyboard::Key::Down) m_player->cInput->down = false;
          if (event.key.code == sf::Keyboard::Key::Up) m_player->cInput->up = false;
          if (event.key.code == sf::Keyboard::Key::Left) m_player->cInput->left = false;
          if (event.key.code == sf::Keyboard::Key::Right) m_player->cInput->right = false;
        }
        break;
      }
    }
  }
}

void Game::sRender()
{
  // Clear window
  m_window.clear(sf::Color::Black);

  // Draw onto window
  switch(m_gameState)
  {
    case GameState::GAME_INIT:
    case GameState::GAME_RUNNING:
    {
      // Draw entities
      for (auto& entity : m_entityManager.getEntities())
      {
        m_window.draw(entity->cShape->circle);
      }
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

void Game::sTransform()
{
  for (auto& entity : m_entityManager.getEntities())
  {
    if (entity->getTag() == "player")
    {
      if (entity->cInput->left)
      {
        entity->cTransform->pos.x += -5.0F;
      }
      if (entity->cInput->right)
      {
        entity->cTransform->pos.x += 5.0F;
      }
      if (entity->cInput->down)
      {
        entity->cTransform->pos.y += 5.0F;
      }
      if (entity->cInput->up)
      {
        entity->cTransform->pos.y += -5.0F;
      }
    }
    //entity->cTransform->pos += entity->cTransform->velocity;
    entity->cShape->circle.setPosition(entity->cTransform->pos.x, entity->cTransform->pos.y);
  }
}
