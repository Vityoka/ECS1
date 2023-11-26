#pragma once

#include <memory>
#include <map>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "animation.h"

class Assets
{
private:
  std::map<std::string, sf::Texture> m_textures;
  std::map<std::string, sf::SoundBuffer> m_sounds;
  std::map<std::string, sf::Font> m_fonts;
  std::map<std::string, Animation> m_animations;

public:
  void loadfromFile(std::string path);
  void addTexture(std::string name, std::string path);
  void addSound(std::string name, std::string path);
  void addFont(std::string name, std::string path);
  void addAnimation(std::string name, std::string path);

  sf::Texture& getTexture(std::string name);
  sf::SoundBuffer& getSound(std::string name); 
  sf::Font& getFont(std::string name);
  Animation& getAnimation(std::string name);
};