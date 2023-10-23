#pragma once

#include <string>
#include <memory>
#include "components.h"

class Entity
{
private:
  const int         m_id = 0;
  const std::string m_tag = "Default";
  bool              m_alive = true;
public:
  std::shared_ptr<CTransform> cTransform = nullptr;
  std::shared_ptr<CInput> cInput = nullptr;
  std::shared_ptr<CShape> cShape = nullptr;
  std::shared_ptr<CScore> cScore = nullptr;
  std::shared_ptr<CBoundingBox> cBoundingBox = nullptr;
  
  Entity(const std::string& tag, int id);
  const std::string& getTag() const;
  bool isAlive() const;
  void destroy();
  //void setCTransform(std::shared_ptr<CTransform>& cTransform){this->cTransform = cTransform;};
  //void setCInput(std::shared_ptr<CInput>& cTransform){this->cInput = cInput;};
  //void setCShape(std::shared_ptr<CShape>& cTransform){this->cShape = cShape;};
  //void setCScore(std::shared_ptr<CScore>& cTransform){this->cScore = cScore;};
};
