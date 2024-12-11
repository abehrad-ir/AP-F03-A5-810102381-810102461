#ifndef STATEMENU_HPP
#define STATEMENU_HPP

#include "states/StateBase.hpp"

class StateMenu : public StateBase {
public:
  StateMenu(std::string text, bool again, sf::RenderWindow *window,
            ResourceManager *resourceManager);
  void update(float time) override;
  void render() override;
  void handleInput(float time) override;

private:
  bool again;
  sf::Text aboveText;
  sf::Text buttonText;
  sf::RectangleShape button;
};

#endif