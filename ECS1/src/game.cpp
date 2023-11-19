#include "game.h"
#include "vec2f.h"
#include <iostream>
#include <random>
#include <fstream>

Game::Game() 
{
  init();
}

void Game::init()
{
  // Load configuration from config.ini
  g_config.loadConfig();

  // Create game window
  m_window.create(sf::VideoMode(g_config.windowConfig.width, g_config.windowConfig.height), "ECS1");
  m_window.setFramerateLimit(g_config.windowConfig.frameRateLimit);
  m_currentFrame = 0U;

  // Time control. Currently overriden with constant to support debugging.
  //m_deltaTime = m_clock.restart().asSeconds();  
  //std::cout << m_deltaTime << std::endl;
  m_deltaTime = 0.017F;  // if real clock is used than in debug mode breakpoint sets infinite time and everything falls apart.

  // Set game state
  m_gameState = GameState::GAME_INIT;

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
}

void Game::run()
{
  while(m_window.isOpen())
  {
    switch (m_gameState)
    {
      case GameState::GAME_INIT:
        sUserInput();
        break;
      case GameState::GAME_RUNNING:
        m_entityManager.update();

        if (!m_paused)
        {
          sEnemySpawner();
          sLifespan();
          sMovement();
          sCollision();
        }
        sUserInput();
        sRender();

        m_currentFrame++;
        break;
      case GameState::GAME_OVER:
        break;
      default:
        break;
    }
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
      // Mouse button pressed event
      case sf::Event::MouseButtonPressed:
      {
        // If any mouse button is pressed go to the next game state
        if (m_gameState == GameState::GAME_INIT)
        {
          m_gameState = GameState::GAME_RUNNING;
          std::cout << "Game has been started" << std::endl; 
        }

        if (event.mouseButton.button == sf::Mouse::Button::Left)
        {
          std::cout << "Left mouse button was clicked at position: " << "x: " << event.mouseButton.x << "y: " << event.mouseButton.y << std::endl; // log message
          spawnBullet( Vec2f(event.mouseButton.x, event.mouseButton.y) );
        }
        if (event.mouseButton.button == sf::Mouse::Button::Right)
        {
          std::cout << "Right mouse button was clicked at position: " << "x: " << event.mouseButton.x << "y: " << event.mouseButton.y << std::endl; // log message
          // DEBUG
          //auto entities = m_entityManager.getEntities();
          //static int i = 0;
          //entities[i]->destroy();
          //i++;
        }
        break;
      }
      // Mouse button released event
      case sf::Event::MouseButtonReleased:
      {
        break;
      }
      // Keyboard pressed event
      case sf::Event::KeyPressed:
      {
        // If any keyboard is pressed go to the next game state
        if (m_gameState == GameState::GAME_INIT)
        {
          m_gameState = GameState::GAME_RUNNING;
          std::cout << "Game has been started" << std::endl; 
        }

        if (event.key.code == sf::Keyboard::Key::P) m_paused = !m_paused;

        //std::cout << event.key.code << std::endl; // log message
        if (m_player->cInput) // Check whether the entity has the cInput component available
        {
          if (event.key.code == sf::Keyboard::Key::Down) m_player->cInput->down = true;
          if (event.key.code == sf::Keyboard::Key::Up) m_player->cInput->up = true;
          if (event.key.code == sf::Keyboard::Key::Left) m_player->cInput->left = true;
          if (event.key.code == sf::Keyboard::Key::Right) m_player->cInput->right = true;
          if (event.key.code == sf::Keyboard::Key::S) m_player->cInput->down = true;
          if (event.key.code == sf::Keyboard::Key::W) m_player->cInput->up = true;
          if (event.key.code == sf::Keyboard::Key::A) m_player->cInput->left = true;
          if (event.key.code == sf::Keyboard::Key::D) m_player->cInput->right = true;
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
          if (event.key.code == sf::Keyboard::Key::S) m_player->cInput->down = false;
          if (event.key.code == sf::Keyboard::Key::W) m_player->cInput->up = false;
          if (event.key.code == sf::Keyboard::Key::A) m_player->cInput->left = false;
          if (event.key.code == sf::Keyboard::Key::D) m_player->cInput->right = false;
        }
        break;
      }
    }
  }
}

void Game::sLifespan()
{
  for (auto& entity : m_entityManager.getEntities())
  {
    if (entity->cLifespan)
    {
      entity->cLifespan->remainingLifespan--;
      if (entity->cLifespan->remainingLifespan <= 0)
      {
        entity->destroy();
      }
      sf::Color color = entity->cShape->circle.getFillColor();
      color.a = 255 * (entity->cLifespan->remainingLifespan / static_cast<float>(entity->cLifespan->totalLifespan));
      entity->cShape->circle.setFillColor(color);
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
        // Set basic rotation for the shapes
        // It is put in the rendering system because in case of a pause, we want rotating shapes
        entity->cTransform->angle += 1.0F;
        if (entity->cTransform->angle > 360.0F)
        {
          entity->cTransform->angle = 0.0F;
        }
        entity->cShape->circle.setRotation(entity->cTransform->angle);

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

void updateBoundingBoxes(std::shared_ptr<Entity>& entity)
{
  // Calculate new bounding boxes for the entities
  entity->cBoundingBox->left = entity->cShape->circle.getGlobalBounds().left;
  entity->cBoundingBox->right = entity->cShape->circle.getGlobalBounds().left + entity->cShape->circle.getGlobalBounds().width;
  entity->cBoundingBox->top = entity->cShape->circle.getGlobalBounds().top ;
  entity->cBoundingBox->bottom = entity->cShape->circle.getGlobalBounds().top + entity->cShape->circle.getGlobalBounds().height;
}

void Game::sMovement()
{
  for (auto& entity : m_entityManager.getEntities())
  {
    if (entity->getTag() == "player")
    {
      const float playerSpeed = 5.0F;
      if (entity->cInput->left)
      {
        float newCoord = entity->cTransform->pos.x - playerSpeed;
        if (newCoord > (0.0F + m_player->cBoundingBox->radius))
        {
          entity->cTransform->pos.x = newCoord;
        }
      }
      if (entity->cInput->right)
      {
        float newCoord = entity->cTransform->pos.x + playerSpeed;
        if (newCoord < (m_window.getSize().x - m_player->cBoundingBox->radius))
        {
          entity->cTransform->pos.x = newCoord;
        }
      }
      if (entity->cInput->down)
      {
        float newCoord = entity->cTransform->pos.y + playerSpeed;
        if (newCoord < (m_window.getSize().y -  + m_player->cBoundingBox->radius))
        {
          entity->cTransform->pos.y = newCoord;
        }
      }
      if (entity->cInput->up)
      {
        float newCoord = entity->cTransform->pos.y - playerSpeed;
        if (newCoord > (0.0F + m_player->cBoundingBox->radius))
        {
          entity->cTransform->pos.y = newCoord;
        }
      }
    }
    if (entity->getTag() == "enemy" ||
        entity->getTag() == "smallEnemy" ||
        entity->getTag() == "bullet")
    {
      entity->cTransform->pos += entity->cTransform->velocity;
    }
    entity->cShape->circle.setPosition(entity->cTransform->pos.x, entity->cTransform->pos.y);

    updateBoundingBoxes(entity);
  }
}

void Game::sCollision()
{
  // Check collision with window boundaries
  for (auto& entity : m_entityManager.getEntities())
  {
    bool isCollision = false;

    // Detect and resolve collision with window edges
    if (entity->cBoundingBox->left < 0.0F ||
        entity->cBoundingBox->right > m_window.getSize().x)
    {
      isCollision = true;
      //std::cout << "collision with window left/right edges" << std::endl;
      entity->cTransform->velocity.x *= -1.0F;
    }
    if (entity->cBoundingBox->top < 0.0F ||
      entity->cBoundingBox->bottom > m_window.getSize().y)
    {
      isCollision = true;
      //std::cout << "collision with window top/bottom edges" << std::endl;
      entity->cTransform->velocity.y *= -1.0F;
    }

    // Check collision with other entities
    // TODO: Detect collision with other entities
    // TODO: Calculate penetration depth
    // TODO: Resolve collision
  }

  for (auto& bullet : m_entityManager.getEntities("bullet"))
  {
    for (auto& enemy : m_entityManager.getEntities("enemy"))
    {
      Vec2f dist (bullet->cTransform->pos - enemy->cTransform->pos);
      if (dist.length() < (enemy->cCollision->radius + bullet->cCollision->radius))
      {
        std::cout << "Collision between bullet and enemy" << std::endl;
        enemy->destroy();
        bullet->destroy();
        spawnSmallEnemies(enemy->cShape->circle.getPointCount(), enemy->cTransform->pos);
      }
    }
    for (auto& smallEnemy : m_entityManager.getEntities("smallEnemy"))
    {
      Vec2f dist (bullet->cTransform->pos - smallEnemy->cTransform->pos);
      if (dist.length() < (smallEnemy->cCollision->radius + bullet->cCollision->radius))
      {
        std::cout << "Collision between bullet and small enemy" << std::endl;
        smallEnemy->destroy();
        bullet->destroy();
      }
    }
  }

  // Check for collision of player with enemies
  for (auto& enemy : m_entityManager.getEntities("enemy"))
  {
    Vec2f dist (m_player->cTransform->pos - enemy->cTransform->pos);
    if (dist.length() < (enemy->cCollision->radius + m_player->cCollision->radius))
    {
      std::cout << "Collision between player and enemy" << std::endl;
      std::cout << "Game over" << std::endl;
      enemy->destroy();
      m_player->destroy();
      m_gameState = GameState::GAME_OVER;
    }
  }
  for (auto& smallEnemy : m_entityManager.getEntities("smallEnemy"))
  {
    Vec2f dist (m_player->cTransform->pos - smallEnemy->cTransform->pos);
    if (dist.length() < (smallEnemy->cCollision->radius + m_player->cCollision->radius))
    {
      std::cout << "Collision between player and small enemy" << std::endl;
      std::cout << "Game over" << std::endl;
      smallEnemy->destroy();
      m_player->destroy();
      m_gameState = GameState::GAME_OVER;
    }
  }

}

void Game::spawnPlayer()
{
  // Get data from config
  const float radius = g_config.playerConfig.shapeRadius;
  sf::Color fillColor = {g_config.playerConfig.fillColorRed, g_config.playerConfig.fillColorGreen, g_config.playerConfig.fillColorBlue};
  sf::Color outlineColor = {g_config.playerConfig.outlineColorRed, g_config.playerConfig.outlineColorGreen, g_config.playerConfig.outlineColorBlue};

  // Create player entity
  m_player = m_entityManager.addEntity("player");

  // Fill player entity
  m_player->cShape = std::make_shared<CShape>(g_config.playerConfig.numOfVertices, radius, fillColor, outlineColor);
  m_player->cInput = std::make_shared<CInput>();
  m_player->cBoundingBox = std::make_shared<CBoundingBox>(radius);
  m_player->cCollision = std::make_shared<CCollision>(radius);

  Vec2f pos (m_window.getSize().x / 2.0F, m_window.getSize().y / 2.0F);
  Vec2f velocity (0, 0);
  m_player->cTransform = std::make_shared<CTransform>(pos, velocity, 0.0F);
}

void Game::spawnBullet( const Vec2f& target )
{
  // Get data from config
  const float bulletSpeed = g_config.bulletConfig.speed;
  const float bulletRadius = g_config.bulletConfig.shapeRadius;
  const int lifespan = g_config.bulletConfig.lifespan;
  sf::Color fillColor = {g_config.bulletConfig.fillColorRed, g_config.bulletConfig.fillColorGreen, g_config.bulletConfig.fillColorBlue};
  sf::Color outlineColor = {g_config.bulletConfig.outlineColorRed, g_config.bulletConfig.outlineColorGreen, g_config.bulletConfig.outlineColorBlue};

  // Create bullet entity
  std::shared_ptr<Entity> bullet = m_entityManager.addEntity("bullet");

  // Calculate direction and velocity vector of the bullet
  Vec2f bulletVelocity = target - m_player->cTransform->pos;
  bulletVelocity.normalize();
  bulletVelocity.scale(bulletSpeed);
  std::cout << "bulletVelocity x: " << bulletVelocity.x << " y: "<< bulletVelocity.y << std::endl;

  // Fill bullet entity
  bullet->cShape = std::make_shared<CShape>(4, bulletRadius, fillColor, outlineColor);
  bullet->cBoundingBox = std::make_shared<CBoundingBox>(bulletRadius);
  bullet->cCollision = std::make_shared<CCollision>(bulletRadius);
  Vec2f pos (m_player->cTransform->pos.x, m_player->cTransform->pos.y);
  Vec2f velocity (bulletVelocity.x, bulletVelocity.y);
  bullet->cTransform = std::make_shared<CTransform>(pos, velocity, 0.0F);
  bullet->cLifespan = std::make_shared<CLifespan>(lifespan, lifespan);
}

void Game::spawnSmallEnemies(int numOfEnemies, Vec2f spawnPosition)
{
  // Get data from config
  const int lifespan = g_config.enemyConfig.smallLifespan;
  float smallEnemySpeed = g_config.enemyConfig.maxSpeed;
  const float smallEnemyRadius = g_config.enemyConfig.shapeRadius / 2.0F;
  
  float angleDifference = (2 * PI_F) / numOfEnemies;
  float startAngle = 0.0F;  // TODO: could be randomized
  for (int i = 0; i < numOfEnemies; i++)
  {
    Vec2f smallEnemyVelocity = Vec2f::polarToDescartes(smallEnemySpeed, startAngle + i * angleDifference);
    std::shared_ptr<Entity> enemy = m_entityManager.addEntity("smallEnemy");
    enemy->cShape = std::make_shared<CShape>(numOfEnemies, smallEnemyRadius, sf::Color::Yellow);
    enemy->cBoundingBox = std::make_shared<CBoundingBox>(smallEnemyRadius);
    enemy->cCollision = std::make_shared<CCollision>(smallEnemyRadius);
    enemy->cTransform = std::make_shared<CTransform>(spawnPosition, smallEnemyVelocity, 0.0F);
    enemy->cLifespan = std::make_shared<CLifespan>(lifespan, lifespan);
  }
}

void Game::spawnEnemy()
{
  // Get data from config
  const int shapeRadius = g_config.enemyConfig.shapeRadius;
  sf::Color fillColor = {g_config.enemyConfig.fillColorRed, g_config.enemyConfig.fillColorGreen, g_config.enemyConfig.fillColorBlue};
  sf::Color outlineColor = {g_config.enemyConfig.outlineColorRed, g_config.enemyConfig.outlineColorGreen, g_config.enemyConfig.outlineColorBlue};

  std::random_device randomDevice;
  std::mt19937 mt(randomDevice());
  std::uniform_real_distribution<double> speedDistribution(g_config.enemyConfig.minSpeed, g_config.enemyConfig.maxSpeed);
  std::uniform_real_distribution<double> angleDistribution(0.0F, 2 * PI_F);
  std::uniform_real_distribution<double> positionXDistribution(0.0 + shapeRadius, m_window.getSize().x - shapeRadius);
  std::uniform_real_distribution<double> positionYDistribution(0.0 + shapeRadius, m_window.getSize().y - shapeRadius);
  std::uniform_int_distribution<int> verticesDistribution(g_config.enemyConfig.minNumOfVertices, g_config.enemyConfig.maxNumOfVertices);

  Vec2f pos (positionXDistribution(mt), positionYDistribution(mt));
  Vec2f velocity = Vec2f::polarToDescartes(speedDistribution(mt), angleDistribution(mt));
  const int numOfVertices = verticesDistribution(mt);

  // Create enemy entity
  std::shared_ptr<Entity> enemy = m_entityManager.addEntity("enemy");

  // Fill enemy entity
  enemy->cShape = std::make_shared<CShape>(numOfVertices, shapeRadius, fillColor, outlineColor);
  enemy->cBoundingBox = std::make_shared<CBoundingBox>(shapeRadius);
  enemy->cCollision = std::make_shared<CCollision>(shapeRadius);
  enemy->cTransform = std::make_shared<CTransform>(pos, velocity, 0.0F);
  // enemy->cTransform = std::make_shared<CTransform>(pos, Vec2f(0, 0), 0.0F);  // Uncomment to have stationary enemies
}

void Game::sEnemySpawner()
{
  static uint64_t lastEnemySpawnedFrame = 0U;
  const uint64_t enemySpawnFrequencyInFrames = g_config.enemyConfig.spawnInterval;

  if ((m_currentFrame - lastEnemySpawnedFrame) > enemySpawnFrequencyInFrames)
  {
    spawnEnemy();
    lastEnemySpawnedFrame = m_currentFrame;
  }
}
