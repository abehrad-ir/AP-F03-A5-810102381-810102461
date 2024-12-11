#include "Game.hpp"
#include "states/StateMenu.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <memory>

using namespace std;

Game::Game()
    : window(make_unique<class sf::RenderWindow>(
          sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE)),
      resourceManager(make_unique<class ResourceManager>()) {
  window->setVerticalSyncEnabled(false);
  window->setKeyRepeatEnabled(false);
  initPlayers();

  states.push(make_unique<class StateMenu>("Welcome!", false, window.get(),
                                           resourceManager.get()));
}

void Game::initPlayers() {

  vector<sf::Keyboard::Key> bindings1 = {
      sf::Keyboard::W,
      sf::Keyboard::S,
      sf::Keyboard::Space,
  };
  vector<sf::Keyboard::Key> bindings2 = {
      sf::Keyboard::Up,
      sf::Keyboard::Down,
      sf::Keyboard::Enter,
  };

  p1 = make_unique<class Player>(
      resourceManager->getConsts()["Player1"], resourceManager->getSheep()[0],
      resourceManager->getConsts()["health"],
      resourceManager->getConsts()["cooldown"], bindings1, posStart1, posQueue1,
      620, false, sf::Vector2f(1.0, 0.0), false, window.get(),
      resourceManager.get());

  p2 = make_unique<class Player>(
      resourceManager->getConsts()["Player2"], resourceManager->getSheep()[1],
      resourceManager->getConsts()["health"],
      resourceManager->getConsts()["cooldown"], bindings2, posStart2, posQueue2,
      620, true, sf::Vector2f(-1.0, 0.0), true, window.get(),
      resourceManager.get());
}
void Game::run() {
  while (window->isOpen()) {
    sf::Event event;
    while (window->pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window->close();
    }
    if (event.type == sf::Event::MouseButtonPressed) {
      if (typeid(*getActiveState()) == typeid(class StateMenu)) {
        states.pop();
        states.push(make_unique<class StateGame>(
            p1.get(), p2.get(), window.get(), resourceManager.get()));
      }
    }
    handleInput();
    update();
    render();
  }
}

void Game::handleInput() {
  if (!states.empty()) {
    getActiveState()->handleInput(time);
  }
}

void Game::update() {
  time = clock.getElapsedTime().asSeconds();
  if (!states.empty()) {
    getActiveState()->update(time);
    if (typeid(*getActiveState()) == typeid(class StateGame)) {
      int exit = static_cast<class StateGame *>(getActiveState())->exit;
      if (exit > 0) {
        states.pop();
        std::string playerName;
        if (exit == 1) {
          playerName = resourceManager->getConsts()["Player1"];
        } else {
          playerName = resourceManager->getConsts()["Player2"];
        }
        states.push(make_unique<class StateMenu>(playerName + " Win!", true, window.get(),
                                                 resourceManager.get()));
      }
    }
  }
  clock.restart();
}

void Game::render() {
  window->clear(sf::Color::White);
  if (!states.empty()) {
    getActiveState()->render();
  }
  window->display();
}

StateBase *Game::getActiveState() {
  if (!states.empty()) {
    return states.top().get();
  }
  return nullptr;
}
