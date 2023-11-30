#include "assets.h"
#include <fstream>
#include <iostream>

void Assets::addTexture(std::string name, std::string path)
{
  sf::Texture texture;
  if (!texture.loadFromFile(path))
  {
    //std::cout << "Texture " << name << " on path " << path << " could not be loaded.\n";
  }
  m_textures[name] = texture;
}
void Assets::addSound(std::string name, std::string path)
{
  sf::SoundBuffer sound;
  if (!sound.loadFromFile(path))
  {
    //std::cout << "Sound " << name << " on path " << path << " could not be loaded.\n";
  }
  m_sounds[name] = sound;
}
void Assets::addFont(std::string name, std::string path)
{
  sf::Font font;
  if (!font.loadFromFile(path))
  {
    //std::cout << "Font " << name << " on path " << path << " could not be loaded.\n";
  }
  m_fonts[name] = font;
}
void Assets::addAnimation(std::string name, std::string path)
{
  sf::Texture texture;
  if (!texture.loadFromFile(path))
  {
    //std::cout << "Animation " << name << " on path " << path << " could not be loaded.\n";
  }
  Animation animation(name, texture);
  m_animations[name] = animation;
}

sf::Texture& Assets::getTexture(std::string name)
{
  return m_textures[name];
}
sf::SoundBuffer& Assets::getSound(std::string name)
{
  return m_sounds[name];
} 
sf::Font& Assets::getFont(std::string name)
{
  return m_fonts[name];
}
Animation& Assets::getAnimation(std::string name)
{
  return m_animations[name];
}

void Assets::loadfromFile(std::string path)
{
  // TODO: load assets from assets.txt
  std::ifstream fin;
  std::string line;
  std::string str;
  fin.open(path);
  std::vector<std::string> configValues;
  static int i = 0;

  if (fin.is_open())
  {
    std::string name;
    bool isTexture = false;
    bool isAnimation = false;
    int i = 0;

    std::cout << "assets.txt found" << std::endl;
    while (fin >> str)
    {
      if (str == "Texture")
      {
        isTexture = true;
      }
      else if (str == "Animation")
      {
        isTexture = true;
      }
      if (isTexture)
      {
        if (i >= 2)
        {
          addTexture(name, str);
          isTexture = false;
          i = 0;
        }
        else
        {
          name = str;
          i++;
        }
      }
      else if(isAnimation)
      {
        if (i >= 2)
        {
          addTexture(name, str);
          isTexture = false;
          i = 0;
        }
        else
        {
          name = str;
          i++;
        }
      }
    }
  }
  else
  {
    std::cout << "assets.txt could not be found" << std::endl;
  }
}