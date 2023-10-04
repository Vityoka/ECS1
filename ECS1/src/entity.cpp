#include "entity.h"

Entity::Entity(const std::string& tag, int id)
  :m_tag (tag)
  ,m_id (id)
{

}

const std::string& Entity::getTag() const
{
  return m_tag;
}

bool Entity::isAlive() const
{
  return m_alive;
}

void Entity::destroy()
{
  m_alive = false;
}

