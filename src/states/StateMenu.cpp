#include "states/StateMenu.hpp"
#include "Game.hpp"

StateMenu::StateMenu(std::string text, bool again, sf::RenderWindow *window,
                     ResourceManager *resourceManager)
    : StateBase(window, resourceManager), button(sf::Vector2f(200, 100)), again(again) {

  button.setFillColor(sf::Color::Blue);
  button.setOutlineColor(sf::Color::Black);
  button.setOutlineThickness(2);

  button.setPosition((WINDOW_WIDTH - button.getSize().x) / 2,
                     (WINDOW_HEIGHT - button.getSize().y) / 2);

  buttonText.setFont(*resourceManager->getFont());
  buttonText.setString(again ? "Start Again" : "Start");
  buttonText.setCharacterSize(24);
  buttonText.setFillColor(sf::Color::White);

  sf::FloatRect buttonTextBounds = buttonText.getLocalBounds();
  buttonText.setOrigin(buttonTextBounds.width / 2, buttonTextBounds.height / 2);
  buttonText.setPosition(button.getPosition().x + button.getSize().x / 2,
                         button.getPosition().y + button.getSize().y / 2 -
                             buttonTextBounds.height / 2);

  aboveText.setFont(*resourceManager->getFont());
  aboveText.setString(text);
  aboveText.setCharacterSize(24);
  aboveText.setFillColor(sf::Color::Black);

  sf::FloatRect aboveTextBounds = aboveText.getLocalBounds();
  aboveText.setOrigin(aboveTextBounds.width / 2, aboveTextBounds.height / 2);
  aboveText.setPosition(button.getPosition().x + button.getSize().x / 2,
                        button.getPosition().y - aboveTextBounds.height - 10);
}

void StateMenu::update(float time) {}

void StateMenu::render() {
  window->clear(sf::Color::Green);
  window->draw(aboveText);
  if (!again) {
    window->draw(buttonText);
    window->draw(button);
  }
  window->display();
}

void StateMenu::handleInput(float time) {}