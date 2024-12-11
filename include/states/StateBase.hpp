#ifndef STATEBASE_HPP
#define STATEBASE_HPP

#include "managers/ResourceManager.hpp"
#include <SFML/Graphics.hpp>
#include "InputHandler.hpp"

class StateBase : public InputHandler {
public:
  StateBase(sf::RenderWindow* window, ResourceManager* resourceManager)
      : InputHandler(), window(window), resourceManager(resourceManager){};

  virtual void update(float time) = 0;

  virtual void render() = 0;

protected:
  sf::RenderWindow* window;
  ResourceManager* resourceManager;
};

#endif
