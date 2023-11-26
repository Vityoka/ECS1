#pragma once

#include "vec2f.h"
#include <memory>
#include "entity.h"

class Physics
{
  Physics();
  Vec2f GetOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b);
  Vec2f GetPreviousOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b);
};