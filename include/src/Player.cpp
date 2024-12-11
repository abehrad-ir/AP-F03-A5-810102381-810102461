#include "entities/Player.hpp"
#include "Game.hpp"
#include "json.hpp"
#include "managers/ResourceManager.hpp"
#include <memory>

using namespace std;

Player::Player(std::string name, nlohmann::json sheepConfig, int health,
               int cooldown, std::vector<sf::Keyboard::Key> keyBindings,
               int startPosX, std::vector<int> queuePosX, int queuePosY,
               bool flipSprites, sf::Vector2f vectorMove, bool flip,
               sf::RenderWindow *window, ResourceManager *resourceManager)
    : name(name), sheepConfig(sheepConfig), health(health), COOLDOWN(cooldown),
      keyBindings(keyBindings), startPosX(startPosX), queuePosX(queuePosX),
      queuePosY(queuePosY), flipSprites(flipSprites), vectorMove(vectorMove),
      flip(flip), activeSheep(GAME_ROWS), window(window),
      resourceManager(resourceManager) {
  addToQueue(3);
}

void Player::render() {
  for (auto &sheep : activeSheep) {
    for (auto &s : sheep)
      s->render(window);
  }
  for (auto &sheep : queueSheep) {
    sheep->render(window);
  }
}

void Player::update(float time, std::vector<float> moves, bool accident) {
  cooldownTimer += time;
  if (cooldownTimer >= 0.001f) {
    if (cooldown > 0)
      cooldown -= (1000 * cooldownTimer);
    else if (cooldown < 0)
      cooldown = 0;
    cooldownTimer = 0;
  }
  if (cooldown <= 0) {
    queueSheep.front()->setStatePending(
        sf::Vector2f(startPosX, posHighlights[highlight]));
  }
  for (int i = 0; i < GAME_ROWS; i++) {
    for (int j = 0; j < activeSheep[i].size(); j++) {
      if (j == 0) {
        if (accident) {
          activeSheep[i][j]->update(time, activeSheep[i][j]->getPositionX(flip),
                                    moves[i]);
        } else {
          activeSheep[i][j]->update(time, flip ? 0 : 1200,
                                    moves[i]);
        }
      } else {
        activeSheep[i][j]->update(
            time, activeSheep[i][j - 1]->getPositionX(flip),
            moves[i], true);
      }
    }
  }
  for (auto &sheep : queueSheep) {
    sheep->update(time, 100, 1.0f);
  }
}

void Player::handleInput(float time) {
  keyTimer += time;
  if (keyTimer >= 0.1f) {
    if (sf::Keyboard::isKeyPressed(keyBindings[0])) {
      keyTimer = 0;
      if (highlight > 0)
        highlight--;
    }
    if (sf::Keyboard::isKeyPressed(keyBindings[1])) {
      keyTimer = 0;
      if (highlight < GAME_ROWS - 1)
        highlight++;
    }
  }
  if (sf::Keyboard::isKeyPressed(keyBindings[2])) {
    if (cooldown == 0) {
      cooldown = COOLDOWN;
      queueSheep[0]->setStateRunning(
          sf::Vector2f(startPosX, posHighlights[highlight]), highlight);
      activeSheep[highlight].push_back(move(queueSheep[0]));
      queueSheep.erase(queueSheep.begin());
      addToQueue();
    }
  }
}

void Player::addToQueue(int num) {
  std::vector<double> cumulativeProbabilities;
  double sum = 0.0;
  for (const auto &entry : sheepConfig) {
    sum += (double)entry["probability"];
    cumulativeProbabilities.push_back(sum);
  }

  random_device rd;
  mt19937 gen(rd());
  uniform_real_distribution<> dis(0.0, 1.0);
  if (num == 1) {
    queueSheep[0]->setStateQueue(sf::Vector2f(queuePosX[0], queuePosY));
    queueSheep[1]->setStateQueue(sf::Vector2f(queuePosX[1], queuePosY));
  }
  for (int i = 0; i < num; ++i) {
    double randomValue = dis(gen);
    for (size_t j = 0; j < cumulativeProbabilities.size(); ++j) {
      if (randomValue <= cumulativeProbabilities[j]) {
        nlohmann::json config = *next(sheepConfig.begin(), j);
        queueSheep.push_back(make_shared<Sheep>(
            config["name"], config["path_move"], config["path_stand"],
            sf::Vector2f(queuePosX[2 - i], queuePosY), vectorMove,
            config["frame_count_move"], config["frame_count_stand"],
            resourceManager->getConsts()["speed"], config["damage"],
            config["strength"], flip));
        break;
      }
    }
  }
}
