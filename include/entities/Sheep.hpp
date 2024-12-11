#ifndef SHEEP_HPP
#define SHEEP_HPP

#include "managers/ResourceManager.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

enum SheepState { InQueue, Running, Pending, InFight };
class Sheep {
public:
  Sheep(std::string name, std::string texturePathMove, std::string textureStand,sf::Vector2f pos, sf::Vector2f vectorMove, int frameCountMove, int frameCountStand, float speed,
        int damage, int strength, bool flip);
  void render(sf::RenderWindow* window);
  void update(float time, int maxX , float vectorSpeed, bool width = false);
  void setStateQueue(sf::Vector2f pos);
  void setStatePending(sf::Vector2f pos);
  void setStateRunning(sf::Vector2f pos, int row_);
  sf::Vector2f getPosition() const;
  float getPositionX(bool sum_width);
  const int damage;
int row;
  const int strength;
  SheepState state = InQueue;
private:
bool flip;
  sf::Sprite sprite;
sf::Vector2f vectorMove;
  void updateTextureRect();
  std::string name;
  ResourceManager resourceManager;
  sf::Texture textureStand;
  sf::Texture textureMove;
  sf::Sprite spritePending;
  int frameCountMove;
  int frameCountStand;
  int currentFrame;
  float frameTime = 0.1f;
  float flashingTime = 1.0f;
  bool isVisible = true;
  float timeSinceLastFrame;
  const float speed;
  sf::Vector2f position;
};

#endif