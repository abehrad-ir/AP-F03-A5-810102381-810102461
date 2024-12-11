#ifndef GAME_HPP
#define GAME_HPP

#include "entities/Player.hpp"
#include "managers/ResourceManager.hpp"
#include "states/StateMenu.hpp"
#include "states/StateBase.hpp"
#include "states/StateGame.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <memory>
#include <stack>

#define GAME_ROWS 4
#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720
#define WINDOW_TITLE "Sheep Fight"

enum GameState
{
  StateMenu,
  StateInGame,
  StatePuased,
  StateFinished
};
class Game {
public:
  Game();
  void run();

private:
const int posStart1 = 20;
const int posStart2 = 960;
const std::vector<int> posQueue1 = {110,210,310};
const std::vector<int> posQueue2 = {900,800,700};
sf::Clock clock;
float time;
void initPlayers();
  void handleInput();
  void update();
  void render();
  void popState();
  StateBase *getActiveState();
  std::unique_ptr<Player> p1;
  std::unique_ptr<Player> p2;
  void pushState(std::unique_ptr<StateBase> state);
  std::stack<std::unique_ptr<StateBase>> states;
  std::unique_ptr<sf::RenderWindow> window;
  std::unique_ptr<ResourceManager> resourceManager;
  GameState state;
};

#endif