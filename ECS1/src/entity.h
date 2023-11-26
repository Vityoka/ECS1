#pragma once

#include "components.h"
#include <tuple>
#include <string>

class EntityManager;

typedef std::tuple<
  CTransform,
  CLifespan,
  CInput, 
  CBoundingBox,
  CAnimation,
  CGravity,
  CState
> ComponentTuple;

class Entity
{  
  bool m_active = true;
  std::string m_tag = "default";
  size_t m_id = 0;
  ComponentTuple m_components;

  // constructor is private so we can never create
  // entities outside the EntityManager which had friend access
  // I HAVE MADE IT PUBLIC, ITS EASIER
  // Entity(const size_t & id, const std::string & tag);
  // friend class EntityManager;

  public:
    Entity(const size_t& id, const std::string& tag);
    void destroy();
    size_t getId() const;
    bool isActive() const;
    const std::string& getTag() const;

  template <typename T>
  bool hasComponent()
  {
    return getComponent<T>().has;
  }

  template<typename T, typename... TArgs>
  T& addComponent(TArgs&&... mArgs)
  {
    auto& component = getComponent<T>();
    component = T(std::forward<TArgs> (mArgs)...); 
    component.has = true;
    return component;
  }

  template<typename T>
  T& getComponent()
  {
    return std::get<T>(m_components);
  }

  template<typename T>
  T& removeComponent()
  {
    getComponent<T>() = T();
  }
};
