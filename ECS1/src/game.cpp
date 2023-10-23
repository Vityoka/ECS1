#include "game.h"
#include "vec2f.h"
#include <iostream>
#include <random>

Game::Game() 
{
  init();
}

void Game::spawnPlayer()
{
  m_player = m_entityManager.addEntity("player");
  m_player->cShape = std::make_shared<CShape>(3, 10, sf::Color::Blue);
  m_player->cInput = std::make_shared<CInput>();
  m_player->cBoundingBox = std::make_shared<CBoundingBox>();

  Vec2f pos (100, 100);
  Vec2f velocity (0, 0);
  m_player->cTransform = std::make_shared<CTransform>(pos, velocity, 0.0F);
}

void Game::init()
{
  // Create game window
  m_window.create(sf::VideoMode(800, 600), "ECS1");
  m_window.setFramerateLimit(60);
  m_currentFrame = 0U;

  // Time control. Currently overriden with constant to support debugging.
  //m_deltaTime = m_clock.restart().asSeconds();  
  //std::cout << m_deltaTime << std::endl;
  m_deltaTime = 0.017F;  // if real clock is used than in debug mode breakpoint sets infinite time and everything falls apart.

  // Set game state
  m_gameState = GameState::GAME_RUNNING;

  spawnPlayer();

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
    sCollision();
    sEnemySpawner();
    
    m_entityManager.update();

    m_currentFrame++;
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
      const float playerSpeed = 5.0F;
      if (entity->cInput->left)
      {
        entity->cTransform->pos.x += -playerSpeed;
      }
      if (entity->cInput->right)
      {
        entity->cTransform->pos.x += playerSpeed;
      }
      if (entity->cInput->down)
      {
        entity->cTransform->pos.y += playerSpeed;
      }
      if (entity->cInput->up)
      {
        entity->cTransform->pos.y += -playerSpeed;
      }
    }
    if (entity->getTag() == "enemy")
    {
      entity->cTransform->pos += entity->cTransform->velocity;
    }
    entity->cShape->circle.setPosition(entity->cTransform->pos.x, entity->cTransform->pos.y);
  }
}

void Game::sCollision()
{
  // Check collision with window boundaries
  for (auto& entity : m_entityManager.getEntities())
  {
    bool isCollision = false;
    
    // Calculate bounding boxes for the entities
    entity->cBoundingBox->left = entity->cShape->circle.getGlobalBounds().left;
    entity->cBoundingBox->right = entity->cShape->circle.getGlobalBounds().left + entity->cShape->circle.getGlobalBounds().width;
    entity->cBoundingBox->top = entity->cShape->circle.getGlobalBounds().top ;
    entity->cBoundingBox->bottom = entity->cShape->circle.getGlobalBounds().top + entity->cShape->circle.getGlobalBounds().height;

    // Detect and resolve collision with window edges
    if (entity->cBoundingBox->left < 0.0F ||
        entity->cBoundingBox->right > m_window.getSize().x)
    {
      isCollision = true;
      std::cout << "collision with window left/right edges" << std::endl;
      entity->cTransform->velocity.x *= -1.0F;
    }
    if (entity->cBoundingBox->top < 0.0F ||
      entity->cBoundingBox->bottom > m_window.getSize().y)
    {
      isCollision = true;
      std::cout << "collision with window top/bottom edges" << std::endl;
      entity->cTransform->velocity.y *= -1.0F;
    }

    // Check collision with other entities
    // TODO: Detect collision with other entities
    // TODO: Calculate penetration depth
    // TODO: Resolve collision
  }
}

void Game::sEnemySpawner()
{
  static uint64_t lastEnemySpawnedFrame = 0U;
  constexpr uint64_t enemySpawnFrequencyInFrames = 60*2;

  std::random_device randomDevice;
  std::mt19937 mt(randomDevice());
  std::uniform_real_distribution<double> speedDistribution(1.0, 4.0);
  std::uniform_real_distribution<double> angleDistribution(0.0, 2*3.14);

  if ((m_currentFrame - lastEnemySpawnedFrame) > enemySpawnFrequencyInFrames)
  {
    std::shared_ptr<Entity> enemy = m_entityManager.addEntity("enemy");

    std::shared_ptr<CShape> enemyShape = std::make_shared<CShape>(3, 10, sf::Color::Blue);
    enemy->cShape = enemyShape;
    Vec2f pos (300, 300);
    Vec2f velocity = Vec2f::polarToDescartes(speedDistribution(mt), angleDistribution(mt));
    std::shared_ptr<CBoundingBox> enemyBBox = std::make_shared<CBoundingBox>();
    enemy->cBoundingBox = enemyBBox;
    std::shared_ptr<CTransform> enemyTransform = std::make_shared<CTransform>(pos, velocity, 0.0F);
    enemy->cTransform = enemyTransform;

    lastEnemySpawnedFrame = m_currentFrame;
  }
}
