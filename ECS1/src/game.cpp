#include "game.h"
#include "vec2f.h"
#include <iostream>
#include <random>
#include <fstream>

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

  // TODO: read config file. BulletConfig, EnemyConfig, etc.
  // std::ifstream fin (path);
  // fin >> m_playerConfig.SR >> m_playerConfig.CR;

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
    m_entityManager.update();

    if (!m_paused)
    {
      sUserInput();
      sEnemySpawner();
      sLifespan();
      sMovement();
      sCollision();
    }
    sRender();

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
      // Mouse button pressed event
      case sf::Event::MouseButtonPressed:
      {
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

void Game::sMovement()
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
    if (entity->getTag() == "enemy" ||
        entity->getTag() == "smallEnemy" ||
        entity->getTag() == "bullet")
    {
      entity->cTransform->pos += entity->cTransform->velocity;
    }
    entity->cShape->circle.setPosition(entity->cTransform->pos.x, entity->cTransform->pos.y);

    // set basic rotation for the shapes
    entity->cTransform->angle += 1.0F;
    if (entity->cTransform->angle > 360.0F)
    {
      entity->cTransform->angle = 0.0F;
    }
    entity->cShape->circle.setRotation(entity->cTransform->angle);
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
}

void Game::spawnBullet( const Vec2f& target )
{
  // Create bullet entity
  std::shared_ptr<Entity> bullet = m_entityManager.addEntity("bullet");

  // Calculate direction and velocity vector of the bullet
  const float bulletSpeed = 5.0F;
  Vec2f bulletVelocity = target - m_player->cTransform->pos;
  bulletVelocity.normalize();
  bulletVelocity.scale(bulletSpeed);
  std::cout << "bulletVelocity x: " << bulletVelocity.x << " y: "<< bulletVelocity.y << std::endl;

  // Fill bullet entity
  const float bulletRadius = 5.0F;
  const int lifespan = 400;
  bullet->cShape = std::make_shared<CShape>(4, bulletRadius, sf::Color::Red);
  bullet->cBoundingBox = std::make_shared<CBoundingBox>();
  bullet->cCollision = std::make_shared<CCollision>(bulletRadius);
  Vec2f pos (m_player->cTransform->pos.x, m_player->cTransform->pos.y);
  Vec2f velocity (bulletVelocity.x, bulletVelocity.y);
  bullet->cTransform = std::make_shared<CTransform>(pos, velocity, 0.0F);
  bullet->cLifespan = std::make_shared<CLifespan>(lifespan, lifespan);
}

void Game::spawnSmallEnemies(int numOfEnemies, Vec2f spawnPosition)
{
  const int lifespan = 200;
  float smallEnemySpeed = 1.0F;
  const float smallEnemyRadius = 5.0F;
  float angleDifference = (2 * PI_F) / numOfEnemies;
  float startAngle = 0.0F;  // TODO: could be randomized
  for (int i = 0; i < numOfEnemies; i++)
  {
    Vec2f smallEnemyVelocity = Vec2f::polarToDescartes(smallEnemySpeed, startAngle + i * angleDifference);
    std::shared_ptr<Entity> enemy = m_entityManager.addEntity("smallEnemy");
    enemy->cShape = std::make_shared<CShape>(5, smallEnemyRadius, sf::Color::Yellow);
    enemy->cBoundingBox = std::make_shared<CBoundingBox>();
    enemy->cCollision = std::make_shared<CCollision>(smallEnemyRadius);
    enemy->cTransform = std::make_shared<CTransform>(spawnPosition, smallEnemyVelocity, 0.0F);
    enemy->cLifespan = std::make_shared<CLifespan>(lifespan, lifespan);
  }
}

void Game::spawnEnemy()
{
  float shapeRadius = 10.0F;

  std::random_device randomDevice;
  std::mt19937 mt(randomDevice());
  std::uniform_real_distribution<double> speedDistribution(1.0, 4.0);
  std::uniform_real_distribution<double> angleDistribution(0.0, 2 * PI_F);
  std::uniform_real_distribution<double> positionXDistribution(0.0 + shapeRadius, m_window.getSize().x - shapeRadius);
  std::uniform_real_distribution<double> positionYDistribution(0.0 + shapeRadius, m_window.getSize().y - shapeRadius);

  Vec2f pos (positionXDistribution(mt), positionYDistribution(mt));
  Vec2f velocity = Vec2f::polarToDescartes(speedDistribution(mt), angleDistribution(mt));

  std::shared_ptr<Entity> enemy = m_entityManager.addEntity("enemy");

  enemy->cShape = std::make_shared<CShape>(5, shapeRadius, sf::Color::Green);
  enemy->cBoundingBox = std::make_shared<CBoundingBox>();
  enemy->cCollision = std::make_shared<CCollision>(shapeRadius);
  enemy->cTransform = std::make_shared<CTransform>(pos, velocity, 0.0F);
  // enemy->cTransform = std::make_shared<CTransform>(pos, Vec2f(0, 0), 0.0F);  // Uncomment to have stationary enemies
}

void Game::sEnemySpawner()
{
  static uint64_t lastEnemySpawnedFrame = 0U;
  constexpr uint64_t enemySpawnFrequencyInFrames = 60*2;

  if ((m_currentFrame - lastEnemySpawnedFrame) > enemySpawnFrequencyInFrames)
  {
    spawnEnemy();
    lastEnemySpawnedFrame = m_currentFrame;
  }
}
