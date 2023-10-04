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
  static float distance(Vec2f lhs, Vec2f rhs);
};

Vec2f operator+(Vec2f lhs, Vec2f rhs);
Vec2f operator-(Vec2f lhs, Vec2f rhs);
float operator* (Vec2f lhs, Vec2f rhs); // implements dot product (scalar product, inner product)
bool operator== (Vec2f lhs, Vec2f rhs);
void operator+= (Vec2f lhs, Vec2f rhs);

