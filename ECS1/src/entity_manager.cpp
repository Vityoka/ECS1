#include "entity_manager.h"
#include "entity.h"
#include <algorithm>

struct IsAlive
{
  bool operator()(std::shared_ptr<Entity> entity)
  {
    return entity->isAlive();
  }
};

struct IsNotAlive
{
  bool operator()(std::shared_ptr<Entity> entity)
  {
    return !entity->isAlive();
  }
};


EntityManager::EntityManager()
{

}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag)
{
  // Create a new Entity object
  m_totalEntities++;
  std::shared_ptr<Entity> newEntity = std::make_shared<Entity>(tag, m_totalEntities);

  // Add new entity to the waiting buffer
  m_toAdd.push_back(newEntity);

  // Return the shared pointer pointing to that entity
  return newEntity;
}

void EntityManager::update()
{
  // Loop through the entities that are waiting to be added
  for (std::shared_ptr<Entity> entity : m_toAdd)
  {
    // Store it in the vector of all entities
    m_entities.push_back(entity);

    // Store it in the map of tag->entityVector
    // This code does not handle some map related edge cases
    m_entityMap[entity->getTag()].push_back(entity);  //Ezt nem ertem a mapet hogy mukodik
  }

  m_toAdd.clear();

  // Loop through the entities that are waiting to be deleted by their isAlive flag
  for (std::shared_ptr<Entity> entity : m_entities)
  {

    if (!entity->isAlive())
    {
      // If we want to delete an element from a vector that we are just iterating through casues
      // iterator invalidation, which we have to deal with here.
      // C++ has a function which can solve this: remove_if()

      // TODO
      
    }
  }
  auto lastAliveElement = std::remove_if(m_entities.begin(), m_entities.end(), IsNotAlive());
  m_entities.erase(lastAliveElement, m_entities.end());

  // TODO: remove from the map too.
}

EntityVector& EntityManager::getEntities()
{
  return m_entities;
}

