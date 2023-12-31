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

Vec2f operator+ (const Vec2f& lhs, const Vec2f& rhs)
{
  Vec2f retVal;
  retVal.x = lhs.x + rhs.x;
  retVal.y = lhs.y + rhs.y;
  return retVal;
}

Vec2f operator- (const Vec2f& lhs, const Vec2f& rhs)
{
  Vec2f retVal;
  retVal.x = lhs.x - rhs.x;
  retVal.y = lhs.y - rhs.y;
  return retVal;
}

float operator* (const Vec2f& lhs, const Vec2f& rhs)
{
  float dotProduct = lhs.x * rhs.x + lhs.y * rhs.y;
  return dotProduct;
}

bool operator== (const Vec2f& lhs, const Vec2f& rhs)
{
  return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

bool operator!= (const Vec2f& lhs, const Vec2f& rhs)
{
  return (lhs.x != rhs.x) || (lhs.y != rhs.y);
}

void operator+= (Vec2f& lhs, const Vec2f& rhs)
{
  lhs.x += rhs.x;
  lhs.y += rhs.y;
}

float Vec2f::distance(const Vec2f& lhs, const Vec2f& rhs)
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
  float len = length();
  if (len > 0)
  {
    x /= len;
    y /= len;
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

Vec2f Vec2f::polarToDescartes(float magnitude, float angle)
{
  Vec2f retVal;
  retVal.x = magnitude * cos(angle);
  retVal.y = magnitude * sin(angle);
  return retVal;
}
