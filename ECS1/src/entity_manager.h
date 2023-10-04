#pragma once

#include "entity.h"
#include <vector>
#include <memory>
#include <map>

// We could store raw entities in the std::vector, but destroying/inserting would be too expensive operation
// therefore we only store pointers to thoes entities.
typedef std::vector<std::shared_ptr<Entity>> EntityVector;

// We will also store separate vectors of Entity objects by their tag for quick retrieval.
// It is a very neat functionality, for which we will have a little tradeoff with memory.
// It will not cost much memory, since only the sotrage of pointers will be duplicated, but the bulk of the
// memory usage is by the Entities itself.
typedef std::map <std::string, EntityVector> EntityMap;

class EntityManager {
private:
  EntityVector m_entities; // Store all entites of the game
  EntityVector m_toAdd; // Buffer to add new entities to the m_entities vector when it is safe to do so
  EntityMap m_entityMap; // Store all entities for a given tag
  int m_totalEntities = 0; // Total number of entities we created during the lifetime of our program
public:
  EntityManager();
  std::shared_ptr<Entity> addEntity(const std::string& tag); // Takes a tag of an entity we want to create and returns a pointer for that entity
  void update();
  EntityVector& getEntities(); // Get all entities
  EntityVector& getEntities(const std::string& tag); // Get specific entities based on their tag
};