#ifndef RESOURCEMANAGERR_HPP
#define RESOURCEMANAGERR_HPP

#include "managers/ResourceManager.hpp"
#include <memory>

using json = nlohmann::json;

ResourceManager::ResourceManager() {
  std::ifstream inputFile(ResourceManager::CONFIG_FILE);
    
    if (!inputFile.is_open()) {
        std::cerr << "Could not open config file!" << std::endl;
        return;
    }
    
    inputFile >> config;
}
const std::shared_ptr<sf::Font> ResourceManager::getFont() {
    if (!font) {
      font = std::make_shared<sf::Font>();
      if (!font->loadFromFile(getPaths()["font"])) {
        std::cout << "Error loading font...\n";
      }
    }
    return font;
  }
const nlohmann::json ResourceManager::getPaths() {
  return config["paths"];
}

const nlohmann::json ResourceManager::getSheep() {
  return config["sheep"];
}

const nlohmann::json ResourceManager::getConsts() {
  return config["constants"];
}

sf::Texture &ResourceManager::getTexture(const std::string &filename) {
  auto it = textures.find(filename);
  if (it == textures.end()) {
    std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>();
    if (!texture->loadFromFile(filename)) {
      throw std::runtime_error("ResourceManager: Failed to load texture: " +
                               filename);
    }
    textures[filename] = std::move(texture);
  }
  return *textures[filename];
}
sf::Font &ResourceManager::getFont(const std::string &filename) {
  auto it = fonts.find(filename);
  if (it == fonts.end()) {
    std::unique_ptr<sf::Font> font = std::make_unique<sf::Font>();
    if (!font->loadFromFile(filename)) {
      throw std::runtime_error("ResourceManager: Failed to load font: " +
                               filename);
    }
    fonts[filename] = std::move(font);
  }
  return *fonts[filename];
}
sf::SoundBuffer &ResourceManager::getSoundBuffer(const std::string &filename) {
  auto it = soundBuffers.find(filename);
  if (it == soundBuffers.end()) {
    std::unique_ptr<sf::SoundBuffer> soundBuffer =
        std::make_unique<sf::SoundBuffer>();
    if (!soundBuffer->loadFromFile(filename)) {
      throw std::runtime_error(
          "ResourceManager: Failed to load sound buffer: " + filename);
    }
    soundBuffers[filename] = std::move(soundBuffer);
  }
  return *soundBuffers[filename];
}

#endif
