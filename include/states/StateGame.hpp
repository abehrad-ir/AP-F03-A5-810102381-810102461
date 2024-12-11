#ifndef STATEGAME_HPP
#define STATEGAME_HPP

#include "entities/Player.hpp"
#include "states/StateBase.hpp"
#include <SFML/Graphics.hpp>
#include "Game.hpp"

class StateGame : public StateBase {
public:
  StateGame(Player* p1, Player* p2, sf::RenderWindow *window, ResourceManager *resourceManager);
  void update(float time) override;
  void render() override;
  void handleInput(float time) override;
  int exit = 0;
private:
  sf::Sprite spBackground;
  sf::Texture txBackground;
  sf::Text textP1;
  sf::Text textP2;
  Player* p1;
  Player* p2;
};

#endif