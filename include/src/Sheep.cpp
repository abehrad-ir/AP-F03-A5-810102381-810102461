#include "entities/Sheep.hpp"
#include <SFML/System/Vector2.hpp>
#include <algorithm>

using namespace std;
using namespace sf;

Sheep::Sheep(string name, std::string texturePathMove,
             std::string texturePathStand, sf::Vector2f pos,
             sf::Vector2f vectorMove, int frameCountMove, int frameCountStand,
             float speed, int damage, int strength, bool flip)
    : name(name), position(pos), vectorMove(vectorMove),
      frameCountMove(frameCountMove), frameCountStand(frameCountStand),
      currentFrame(0), timeSinceLastFrame(0.0f), speed(speed), damage(damage),
      strength(strength), flip(flip) {

  if (!textureStand.loadFromFile(texturePathStand)) {
    std::cerr << "Error loading texture!" << std::endl;
  }

  if (!textureMove.loadFromFile(texturePathMove)) {
    std::cerr << "Error loading texture!" << std::endl;
  }

  sprite.setTexture(textureStand);
  spritePending.setTexture(textureStand);

  updateTextureRect();

  sprite.setPosition(position);
  spritePending.setPosition(position);
}

void Sheep::setStateQueue(sf::Vector2f pos) {
  state = SheepState::InQueue;
  position = pos;
  sprite.setPosition(position);
  updateTextureRect();
}

void Sheep::setStatePending(sf::Vector2f pos) {
  sprite.setTexture(textureStand);
  state = SheepState::Pending;
  spritePending.setPosition(pos);
  updateTextureRect();
}

void Sheep::setStateRunning(sf::Vector2f pos, int row_) {
  row = row_;
  sprite.setTexture(textureMove);
  state = SheepState::Running;
  position = pos;
  sprite.setPosition(position);
  updateTextureRect();
}
sf::Vector2f Sheep::getPosition() const { return sprite.getPosition(); }
void Sheep::update(float time, int maxX, float vectorSpeed, bool width) {
  switch (state) {
  case InQueue:
    timeSinceLastFrame += time;

    if (timeSinceLastFrame >= frameTime) {
      timeSinceLastFrame = 0.0f;
      currentFrame = (currentFrame + 1) % frameCountStand;
      updateTextureRect();
    }
    break;
  case Pending:
    // timeSinceLastFrame += time;
    // if (timeSinceLastFrame >= flashingTime) {
    //   timeSinceLastFrame = 0.0f;
    //   isVisible = !isVisible;
    // }
    timeSinceLastFrame += time;

    if (timeSinceLastFrame >= frameTime) {
      timeSinceLastFrame = 0.0f;
      currentFrame = (currentFrame + 1) % frameCountStand;
      updateTextureRect();
    }
    break;
  case InFight:
    timeSinceLastFrame += time;

    if (timeSinceLastFrame >= frameTime) {
      timeSinceLastFrame = 0.0f;
      currentFrame = (currentFrame + 1) % frameCountMove;
      updateTextureRect();
    }

    if (vectorSpeed >= -1.0f && vectorSpeed <= 1.0f)
      position += vectorMove * speed * time * vectorSpeed;
    else
      position += vectorMove * speed * time;
    sprite.setPosition(position);

    break;
  case Running:
    timeSinceLastFrame += time;

    if (timeSinceLastFrame >= frameTime) {
      timeSinceLastFrame = 0.0f;
      currentFrame = (currentFrame + 1) % frameCountMove;
      updateTextureRect();
    }

    float move;
    move = speed * time;
    if (!flip && move <= maxX - getPositionX(!flip)) {
      position += vectorMove * move;
    } else if (flip && move <= getPositionX(!flip) - maxX) {
      position += vectorMove * move;
    } else {
      position = Vector2f(width && !flip? maxX - (textureMove.getSize().x / frameCountMove) : maxX, position.y);
      state = SheepState::InFight;
    }
    sprite.setPosition(position);
    break;
  }
}
float Sheep::getPositionX(bool sum_width) {
  float res = sprite.getPosition().x;
  if (sum_width)
    res += sprite.getGlobalBounds().width;
  return res;
}
void Sheep::render(RenderWindow *window) {
  window->draw(sprite);
  if (state == SheepState::Pending)
    window->draw(spritePending);
}

void Sheep::updateTextureRect() {
  if (state == SheepState::InQueue || state == SheepState::Pending) {
    int frameWidth = textureStand.getSize().x / frameCountStand;
    sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth,
                                      textureStand.getSize().y));
    if (state == SheepState::Pending)
      spritePending.setTextureRect(sf::IntRect(
          currentFrame * frameWidth, 0, frameWidth, textureStand.getSize().y));
  } else if (state == SheepState::Running) {
    int frameWidth = textureMove.getSize().x / frameCountMove;
    sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth,
                                      textureMove.getSize().y));
  }
}
