#include "states/StateGame.hpp"
#include "Game.hpp"
#include "entities/Sheep.hpp"
#include <SFML/System/Vector2.hpp>
#include <algorithm>
#include <cmath>

using namespace sf;
using namespace std;

StateGame::StateGame(Player *p1, Player *p2, RenderWindow *window,
                     ResourceManager *resourceManager)
    : StateBase(window, resourceManager), p1(p1), p2(p2) {

  if (!txBackground.loadFromFile(resourceManager->getPaths()["boardgame"])) {
    cout << "Connot load background\n";
    return;
  }
  spBackground.setTexture(txBackground);
  Vector2u windowSize = window->getSize();
  Vector2u textureSize = txBackground.getSize();

  float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
  float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

  spBackground.setScale(scaleX, scaleY);

  textP1.setFont(*resourceManager->getFont());
  textP1.setCharacterSize(20);
  textP1.setFillColor(sf::Color::White);
  textP1.setPosition(110, 52);
  textP2.setFont(*resourceManager->getFont());
  textP2.setCharacterSize(20);
  textP2.setFillColor(sf::Color::White);
}

void StateGame::update(float time) {
  textP1.setString(p1->name + ": " + std::to_string(p1->health));
  textP2.setString(std::to_string(p2->health) + " :" + p2->name);
  sf::FloatRect textBounds = textP2.getLocalBounds();
  textP2.setPosition(WINDOW_WIDTH - textBounds.width - 110, 52);

  std::vector<float> p1Move(GAME_ROWS, 1.0f);
  std::vector<float> p2Move(GAME_ROWS, 1.0f);
  std::vector<float> p1Strength(GAME_ROWS, 0.0f);
  std::vector<float> p2Strength(GAME_ROWS, 0.0f);
  bool accident = false;
  for (int i = 0; i < GAME_ROWS; i++) {
    for (auto it = p1->activeSheep[i].begin(); it < p1->activeSheep[i].end();
         it++) {
      if ((*it)->getPosition().x == NAN ||
          (*it)->getPosition().x > WINDOW_WIDTH - 100) {
        p2->health -= (*it)->damage;
        p1->activeSheep[i].erase(it);
      }

      if (!((*it)->getPosition().x > 10 && (*it)->getPosition().x < 1050))
        p1->activeSheep[i].erase(it);
      if ((*it)->state == SheepState::InFight)
        p1Strength[i] += (*it)->strength;
    }
    for (auto it = p2->activeSheep[i].begin(); it < p2->activeSheep[i].end();
         it++) {
      if ((*it)->getPosition().x == NAN || (*it)->getPosition().x < 50) {
        p1->health -= (*it)->damage;
        p2->activeSheep[i].erase(it);
      }
      if (!((*it)->getPosition().x > 10 && (*it)->getPosition().x < 1050))
        p2->activeSheep[i].erase(it);
      if ((*it)->state == SheepState::InFight)
        p2Strength[i] += (*it)->strength;
    }

    if (!p1->activeSheep[i].empty() && !p2->activeSheep[i].empty()) {
      float pos1 = p1->activeSheep[i].front()->getPositionX(true);
      float pos2 = p2->activeSheep[i].front()->getPositionX(false);

      if (pos2 - pos1 <= 0) {
        accident = true;
        float speed =
            (p1Strength[i] - p2Strength[i]) / max(p1Strength[i], p2Strength[i]);
        p1Move[i] = speed;
        p2Move[i] = -speed;
      }
    }
  }
  p1->update(time, p1Move, accident);
  p2->update(time, p2Move, accident);
  if (p1->health <= 0) {
    exit = 2;
  } else 
  if (p2->health <= 0) {
    exit = 1;
  }
}

void StateGame::render() {
  window->draw(spBackground);
  window->draw(textP1);
  window->draw(textP2);
  p1->render();
  p2->render();
}

void StateGame::handleInput(float time) {
  p1->handleInput(time);
  p2->handleInput(time);
}