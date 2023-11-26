#pragma once
#include "vec2f.h"
#include <SFML/Graphics.hpp>
#include "animation.h"
#include "assets.h"

class Component
{
public:
  bool has = false;
};

class CTransform : public Component
{
public:
  Vec2f pos      = {0.0, 0.0};
  Vec2f prevPos  = {0.0, 0.0};
  Vec2f scale    = {1.0, 1.0};
  Vec2f velocity = {0.0, 0.0};
  float angle    = 0.0F;

  CTransform() {};
  CTransform(const Vec2f& p) 
    : pos(p) {}
  CTransform(const Vec2f& p, const Vec2f& sp, const Vec2f& sc, float a)
    : pos(p)
    , prevPos(p)
    , velocity(sp)
    , scale(sc)
    , angle(a){}
};

class CLifespan : public Component
{
public:
  int lifespan = 0;
  int frameCreated = 0;
  CLifespan () {}
  CLifespan (int duration, int frame)
    : lifespan (duration), frameCreated(frame) {}
};

class CInput : public Component
{
public:
  bool up = false;
  bool down = false;
  bool left = false;
  bool right = false;
  bool shoot   = false;
  bool canShoot = true;
  bool canJump  = true;
  CInput() {}
};

class CBoundingBox : public Component
{
public:
  Vec2f size;
  Vec2f halfSize;
  CBoundingBox() {}
  CBoundingBox(const Vec2f& s)
    : size(s), halfSize(s.x / 2, s.y / 2) {}
};

class CAnimation : public Component
{
public:
  Animation animation;
  bool repeat = false;
  CAnimation() {};
  CAnimation(const Animation& animation, bool r = false) : animation (animation), repeat (r) {};
};

class CGravity : public Component
{
public:
  float gravity= 0;
  CGravity() {}
  CGravity (float g): gravity (g) {}
};

class CState : public Component
{
public:
  std::string state = "jumping"; 
  CState() {}
  CState(const std::string& s): state(s) {}
};
