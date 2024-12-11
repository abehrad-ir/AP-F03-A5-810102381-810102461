#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "entities/Sheep.hpp"
#include "json.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <memory>
#include <random>
#include <vector>
class Player {
public:
  Player(std::string name, nlohmann::json sheepConfig, int health, int cooldown,
         std::vector<sf::Keyboard::Key> keyBindings, int startPosX,
         std::vector<int> queuePosX, int queuePosY, bool flipSprites, sf::Vector2f vectorMove, bool filp,
         sf::RenderWindow *window, ResourceManager *resourceManager);
  void render();
  void update(float time, std::vector<float> moves, bool accident);
  void handleInput(float time);
  std::vector<std::vector<std::shared_ptr<Sheep>>> activeSheep;
  int health;
  std::string name;

private:
bool flip;
  sf::Vector2f vectorMove;
  bool flipSprites = false;
  float keyTimer = 0;
  const std::vector<int> posHighlights = {100, 250, 400, 550};
  int queuePosY;
  const int COOLDOWN;
  int cooldown = 0;
  float cooldownTimer = 0;
  int highlight = 0;
  int startPosX;
  std::vector<int> queuePosX;
  nlohmann::json sheepConfig;
  std::vector<std::shared_ptr<Sheep>> queueSheep;
  ResourceManager *resourceManager;
  sf::RenderWindow *window;
  const std::vector<sf::Keyboard::Key> keyBindings;
  void addToQueue(int num = 1);
};

#endif