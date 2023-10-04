#pragma once

#include <string>
#include <memory>

class Entity
{
private:
  const int         m_id = 0;
  const std::string m_tag = "Default";
  bool              m_alive = true;
public:
  //std::shared_ptr<CTransform> cTransform;
  //std::shared_ptr<CName> cName;
  //std::shared_ptr<CShape> cShape;
  //std::shared_ptr<CBox> cBox;
  Entity(const std::string& tag, int id);
  const std::string& getTag() const;
  bool isAlive() const;
  void destroy();
};
