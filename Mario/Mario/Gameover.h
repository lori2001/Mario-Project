#pragma once
#include "SFML/Graphics.hpp"
#include "Score.h"
#include "Resources.h"
#include "Button.h"

class Gameover {
private:
	sf::Vector2f mouse; // holds position of the mouse
	sf::Text gameover{"GAME OVER", Resources::super_marioF, 200};

	UI::Button goback{ Resources::super_marioF, "Back to Menu", {500, 65} };
	UI::Button exit{ Resources::super_marioF, "Exit", {500, 65} };

	Score score;

	bool isActive = false;
public:
	bool getisActive() const { return isActive; }

	void Setup();
	void handleEvents(const sf::RenderWindow &window, const sf::Event &event);
	void Update(sf::RenderWindow &window);
	void Compose(sf::RenderWindow &window);
};