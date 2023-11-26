#include "assets.h"

  void Assets::addTexture(std::string name, std::string path)
  {
    sf::Texture texture;
    texture.loadFromFile(path);
    m_textures[name] = texture;
  }
  void Assets::addSound(std::string name, std::string path)
  {
    sf::SoundBuffer sound;
    sound.loadFromFile(path);
    m_sounds[name] = sound;
  }
  void Assets::addFont(std::string name, std::string path)
  {
    sf::Font font;
    font.loadFromFile(path);
    m_fonts[name] = font;
  }
  void Assets::addAnimation(std::string name, std::string path)
  {
    sf::Texture texture;
    texture.loadFromFile(path);
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
  }