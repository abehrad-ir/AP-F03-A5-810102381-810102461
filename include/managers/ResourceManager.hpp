#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include "json.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <string>

class ResourceManager {
public:
  ResourceManager();
  sf::Texture &getTexture(const std::string &filename);
  sf::Font &getFont(const std::string &filename);
  sf::SoundBuffer &getSoundBuffer(const std::string &filename);
  const nlohmann::json getPaths();  
  const nlohmann::json getSheep();  
  const nlohmann::json getConsts();  
  const std::shared_ptr<sf::Font> getFont();
private:
  std::shared_ptr<sf::Font> font;
  nlohmann::json config;
  const std::string CONFIG_FILE = "./assets/config.json";
  std::map<std::string, std::unique_ptr<sf::Texture>> textures;
  std::map<std::string, std::unique_ptr<sf::Font>> fonts;
  std::map<std::string, std::unique_ptr<sf::SoundBuffer>> soundBuffers;
};

#endif