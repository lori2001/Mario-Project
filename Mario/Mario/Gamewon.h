#pragma once
#include "SFML/Graphics.hpp"
#include "Score.h"
#include "Resources.h"
#include "Button.h"

class Gamewon {
private:
	sf::Vector2f mouse; // holds position of the mouse
	sf::Text gameWon{ "MAP COMPLETED!", Resources::super_marioF, 200 };

	UI::Button goBack{ Resources::super_marioF, "Back to Menu", {500, 65} };
	UI::Button goOn{ Resources::super_marioF, "Continue", {500, 65} };

	Score score;

	bool isActive = false; // signals if the screen is still active
	bool cont; // true whether user decides to continue
public:
	bool getisActive() const { return isActive; }
	bool getContinue() { return cont; }

	void Setup(const bool worldWon);
	void handleEvents(const sf::RenderWindow &window, const sf::Event &event);
	void Update();
	void Compose(sf::RenderWindow &window);
};