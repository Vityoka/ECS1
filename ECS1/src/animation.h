#pragma once

#include <string>
#include "vec2f.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Animation
{
private:
  sf::Sprite m_sprite;
  size_t m_frameCount   = 1; // total number of frames in the animation
  size_t m_gameFrame    = 0; // how long the current animation is being played in frames
  size_t m_speed        = 0; // the speed to play this animation
  Vec2f  m_size         = {1, 1}; // size of the animation frame
  std::string m_name    = "none";

public:
  Animation();
  Animation (const std::string& name, const sf::Texture& t);
  Animation (const std::string& name, const sf::Texture& t, size_t frameCount, size_t speed);

  void update();
  bool hasEnded() const;
  const std::string& getName() const;
  const Vec2f& getSize() const;
  sf::Sprite& getSprite();
};