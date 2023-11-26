#include "entity.h"

Entity::Entity(const size_t & id, const std::string & tag)
  : m_tag (tag)
  , m_id (id)
{

}

const std::string& Entity::getTag() const
{
  return m_tag;
}

size_t Entity::getId() const
{
  return m_id;
}

bool Entity::isActive() const
{
  return m_active;
}

void Entity::destroy()
{
  m_active = false;
}

