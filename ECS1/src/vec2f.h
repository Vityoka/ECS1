#pragma once

class Vec2f {

private:


public:
  float x;
  float y;

  Vec2f(void);
  Vec2f(float x, float y);
  float length() const;
  float angle() const;

  void normalize();
  void rotate(float angle);
  void scale(float scaleFactor);
  static float distance(const Vec2f& lhs, const Vec2f& rhs);
  static Vec2f polarToDescartes(float magnitude, float angle);
};

Vec2f operator+(const Vec2f& lhs, const Vec2f& rhs);
Vec2f operator-(const Vec2f& lhs, const Vec2f& rhs);
float operator* (const Vec2f& lhs, const Vec2f& rhs); // implements dot product (scalar product, inner product)
bool operator== (const Vec2f& lhs, const Vec2f& rhs);
bool operator!= (const Vec2f& lhs, const Vec2f& rhs);
void operator+= (Vec2f& lhs, const Vec2f& rhs);

