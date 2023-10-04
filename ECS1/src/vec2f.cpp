#include "vec2f.h"
#include <cmath>

Vec2f::Vec2f(void)
{
  this->x = 0.0F;
  this->y = 0.0F;
}

Vec2f::Vec2f(float x, float y)
{
  this->x = x;
  this->y = y;
}

Vec2f operator+ (Vec2f lhs, Vec2f rhs)
{
  Vec2f retVal;
  retVal.x = lhs.x + rhs.x;
  retVal.y = lhs.y + rhs.y;
  return retVal;
}

Vec2f operator- (Vec2f lhs, Vec2f rhs)
{
  Vec2f retVal;
  retVal.x = lhs.x - rhs.x;
  retVal.y = lhs.y - rhs.y;
  return retVal;
}

float operator* (Vec2f lhs, Vec2f rhs)
{
  float dotProduct = lhs.x * rhs.x + lhs.y * rhs.y;
  return dotProduct;
}

bool operator== (Vec2f lhs, Vec2f rhs)
{
  return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

void operator+= (Vec2f lhs, Vec2f rhs)
{
  lhs.x += rhs.x;
  lhs.y += rhs.y;
}

float Vec2f::distance(Vec2f lhs, Vec2f rhs)
{
  Vec2f distanceVector = lhs - rhs;
  return distanceVector.length();
}

float Vec2f::angle() const
{
  return atan2(y, x);
}

float Vec2f::length() const
{
  return sqrtf(x * x + y * y);
}

void Vec2f::normalize()
{
  if (length() > 0)
  {
    x /= length();
    y /= length();
  }
}

void Vec2f::rotate(float angle)
{
  float len = length();
  x = len * cos(angle);
  y = len * sin(angle);
}

void Vec2f::scale(float scaleFactor)
{
  x *= scaleFactor;
  y *= scaleFactor;
}
