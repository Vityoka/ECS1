#include "scene_play.h"
#include "physics.h"
#include "assets.h"
#include "game_engine.h"
#include "components.h"
#include "action.h"
#include <iostream>

ScenePlay::ScenePlay(GameEngine* gameEngine, const std::string & levelPath)
  : Scene(gameEngine)
  , m_levelPath(levelPath)
  {
    init(m_levelPath);
  }

void ScenePlay::init(const std::string& levelPath)
{
  registerAction(sf::Keyboard::Escape, "QUIT");
  registerAction(sf::Keyboard::P, "PAUSE");
  registerAction(sf::Keyboard::T, "TOGGLE TEXTURE");  // Toggle drawing (T)extures 
  registerAction(sf::Keyboard::C, "TOGGLE_COLLISION"); // Toggle drawing (C)ollision Boxes /
  registerAction(sf::Keyboard::G, "TOGGLE_GRID"); // Toggle drawing (G)rid
  
  // TODO: Register all other gameplay Actions
  m_gridText.setCharacterSize (12);
  m_gridText.setFont(m_game->assets().getFont("Tech"));
  
  loadLevel(levelPath);
}

Vec2f ScenePlay::gridtoMidPixel (float gridX, float gridY, std::shared_ptr<Entity> entity)
{
// TODO: This function takes in a grid (x,y) position and an Entity
// Return a Vec2 indicating where the CENTER position of the Entity should be 
// You must use the Entity's Animation size to position it correctly
// The size of the grid width and height is stored in m_gridSize.x and m_gridSize.y
// The bottom-left corner of the Animation should align with the bottom left of the grid cell
  return Vec2f(0, 0);
}

void ScenePlay::loadLevel (const std::string & filename)
{
  // reset the entity manager every time we load a level 
  m_entityManager = EntityManager();

  // TODO: read in the level file and add the appropriate entities
  //   use the PlayerConfig struct m_playerConfig to store player properties 
  //   this struct is defined at the top of ScenePlay.h
  // NOTE: all of the code below is sample code which shows you how to
  //   set up and use entities with the new syntax, it should be removed

  spawnPlayer();

  // some sample entities
  auto brick = m_entityManager.addEntity("tile");

  // IMPORTANT: always add the CAnimation component first so that gridToMid Pixel can compute correctly
  brick->addComponent<CAnimation>(m_game->assets().getAnimation("Brick"), true);
  brick->addComponent<CTransform> (Vec2f(96, 480));

  // NOTE: You final code should position the entity with the grid x,y position read from the file:
  // brick->addComponent<CTransform> (gridToMidPixel (gridX, gridy, brick);

  if (brick->getComponent<CAnimation>().animation.getName() == "Brick")
  {
    std::cout << "This could be a good way identifying if a tile is a brick!\n";
  }

  auto block = m_entityManager.addEntity("tile");
  block->addComponent<CAnimation> (m_game->assets().getAnimation("Block"), true);
  block->addComponent<CTransform> (Vec2f(224, 480));
  // add a bounding box, this will now show up if we press the 'C' key
  block->addComponent<CBoundingBox> (m_game->assets().getAnimation("Block").getSize());

  auto question = m_entityManager.addEntity("tile");
  question->addComponent<CAnimation>(m_game->assets().getAnimation("Question"), true);
  question->addComponent<CTransform> (Vec2f(352, 480));

  // NOTE: THIS IS INCREDIBLY IMPORTANT PLEASE READ THIS EXAMPLE
  //Components are now returned as references rather than pointers
  //If you do not specify a reference variable type, it will COPY the component 
  // Here is an example:
  // 
  // This will COPY the transform into the variable 'transform1' - it is INCORRECT 
  // Any changes you make to transform1 will not be changed inside the entity 
  // auto transform1 = entity->get<CTransform>()
  //
  // This will REFERENCE the transform with the variable 'transform2' - it is CORRECT
  // Now any changes you make to transform2 will be changed inside the entity
  // auto& transform2 = entity->get<CTransform>()
}

void ScenePlay::spawnPlayer()
{
  // here is a sample player entity which you can use to construct other entities 
  m_player = m_entityManager.addEntity("player");
  m_player->addComponent<CAnimation> (m_game->assets().getAnimation ("Stand"), true);
  m_player->addComponent<CTransform> (Vec2f(224, 352)); 
  m_player->addComponent<CBoundingBox> (Vec2f(48, 48)); 
  m_player->addComponent<CGravity>(0.1F);

  // TODO: be sure to add the remaining components to the player
}

void ScenePlay::spawnBullet (std::shared_ptr<Entity> entity)
{
// TODO: this should spawn a bullet at the given entity, going in the direction the entity is facing
}

void ScenePlay::sLifespan ()
{
  // TODO: Check lifespawn of entities that have them, and destroy them if they go over 
}

void ScenePlay::sCollision()
{

// REMEMBER: SFML's (0,0) position is on the TOP-LEFT corner
// This means jumping will have a negative y-component
// and gravity will have a positive y-component
// Also, something BELOW something else will have a y value GREATER than it 
// Also, something ABOVE something else will have a y value LESS than it


// TODO: Implement Physics::GetOverlap () function, use it inside this function
// TODO:  Implement bullet / tile collisions
//        Destroy the tile if it has a Brick animation
// TODO: Implement player tile collisions and resolutions
//       Update the cState component of the player to store whether
//       it is currentlyon the ground or in the air. This will be used by the Animation system
// TODO: Check to see if the player has fallen down a hole (y > height())
// TODO: Dont let the player walk off the left side of the map
}

void ScenePlay::sMovement()
{
  Vec2f playerVelocity (0, 0);
  if (m_player->getComponent<CInput>().up)
  {
    m_player->getComponent<CState>().state = "run";
    playerVelocity.y = -3;
  }
  m_player->getComponent<CTransform>().velocity = playerVelocity;

  for (auto e : m_entityManager.getEntities())
  {
    e->getComponent<CTransform>().pos += e->getComponent<CTransform>().velocity;
  }

  // TODO: Implement player movement jumping based on its CInput component 
  // TODO: Implement gravity's effect on the player
  // TODO: Implement the maxmimum player speed in both X and Y directions
  // NOTE: Setting an entity's scale.x to -1/1 will make it face to the left/right
}

void ScenePlay::update()
{
  m_entityManager.update();
  // TODO: implement pause functionality
  sMovement();
  sLifespan();
  sCollision();
  sAnimation();
  sRender();
}


void ScenePlay::sDoAction (const Action& action)
{
  if (action.type() == "START")
    if (action.name() == "TOGGLE TEXTURE") { m_drawTextures = !m_drawTextures; } 
    else if  (action.name() == "TOGGLE_COLLISION") { m_drawCollision = !m_drawCollision; } 
    else if (action.name() == "TOGGLE_GRID") { m_drawGrid = !m_drawGrid; }
     else if (action.name()  == "PAUSE") { setPaused(m_paused); }
    else if (action.name() == "QUIT") { onEnd(); }
    else if (action.name() == "UP")
    {
      m_player->getComponent<CInput>().up = true;
    }

  else if (action.type() == "END")
  {
    if (action.name() == "UP")
    {
      m_player->getComponent<CInput>().up = false;


      //...
    }
  }
}

void ScenePlay::sAnimation()
{
  // TODO: Complete the Animation class code first

  if (m_player->getComponent<CState>().state == "air")
  {
    m_player->addComponent<CAnimation> (m_game->assets().getAnimation("Air"));
  }

  // TODO: set the animation of the player based on its CState component
  // TODO: for each entity with an animation, call entity->getComponent<CAnimation>().animation.update()
  //       if the animation is not repeated, and it has ended, destroy the entity
}

void ScenePlay::onEnd()
{
  // TODO: When the scene ends, change back to the MENU scene
  // use m_game->changeScene (correct params);
}

void ScenePlay::sRender()
{
  // color the background darker so you know that the game is paused
  if (!m_paused)
  {
    m_game->window().clear(sf:: Color (100, 100, 255)); 
  }
  else
  {
    m_game->window().clear(sf::Color (50, 50, 150));
  }

  // set the viewport of the window to be centered on the player if it's far enough right
  auto& pPos = m_player->getComponent<CTransform>().pos;
  float windowCenterX = std::max(m_game->window().getSize().x / 2.0f, pPos.x);
  sf::View view = m_game->window().getView();

  view.setCenter(windowCenterX, m_game->window().getSize().y - view.getCenter().y); 
  m_game->window().setView(view);

  // draw all Entity textures / animations
  if (m_drawTextures)
  {
    for (std::shared_ptr<Entity> e : m_entityManager.getEntities())
    {
      auto& transform = e->getComponent<CTransform>();

      if (e->hasComponent<CAnimation>())
      {
        auto& animation = e->getComponent<CAnimation>().animation; 
        animation.getSprite().setRotation (transform. angle);
        animation.getSprite().setPosition(transform.pos.x, transform.pos.y);
        animation.getSprite().setScale (transform.scale.x, transform.scale.y);
        m_game->window().draw(animation.getSprite());
      }
    }
  }

  // draw all Entity collision bounding boxes with a rectangleshape 
  if (m_drawCollision)
  {
    for (auto e : m_entityManager.getEntities())
    {
      
      if (e->hasComponent<CBoundingBox>())
      {
        auto& box = e->getComponent<CBoundingBox>();
        auto& transform = e->getComponent<CTransform>(); 
        sf::RectangleShape rect;
        rect.setSize(sf::Vector2f(box.size.x-1, box.size.y-1));
        rect.setOrigin (sf:: Vector2f(box. halfSize.x, box. halfSize.y));
        rect.setPosition(transform.pos.x, transform.pos.y); 
        rect.setFillColor (sf::Color(0, 0, 0, 0));
        rect.setOutlineColor(sf::Color(255, 255, 255, 255));
        rect.setOutlineThickness(1);
        m_game->window().draw(rect);
      }
      
    }
  }

  // draw the grid so that students can easily debug
  if (m_drawGrid)
  {
    float leftX = m_game->window().getView().getCenter().x - width() / 2;
    float rightX = leftX + width() + m_gridSize.x;
    float nextGridX = leftX - ((int) leftX % (int)m_gridSize.x);

    for (float x = nextGridX; x < rightX; x += m_gridSize.x)
    {
      drawLine(Vec2f(x, 0), Vec2f(x, static_cast<float>(height())));
    }

    for (float y = 0; y < height(); y += m_gridSize.y)
    {
      drawLine(Vec2f(leftX, height() - y), Vec2f(rightX, height() - y));
      for (float x = nextGridX; x < rightX; x += m_gridSize.x)
      {
        std::string xCell = std::to_string((int)x / (int)m_gridSize.x);
        std::string yCell = std::to_string((int)y / (int)m_gridSize.y);

        m_gridText.setString("(" + xCell + "," + yCell + ")");
        m_gridText.setPosition(x + 3, height() - y - m_gridSize.y + 2);
        m_game->window().draw(m_gridText);
      }
    }
  }
}


