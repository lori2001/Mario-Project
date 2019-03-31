#pragma once
#include "SFML/Graphics.hpp"
#include "Resources.h"
#include "Button.h"

class Menu {
private:
	sf::Vector2f mouse; //holds position of the mouse

	UI::Button startgame{ Resources::super_marioF, "Start Game", {430, 50} };
	UI::Button exitgame{ Resources::super_marioF, "Exit", {430, 50}};

	int arrowCount = 1;

	bool isActive = true;
public:
	void setActive(const bool &active) { isActive = active; }
	bool getActive() const { return isActive; }

	void Setup(sf::RenderWindow &window);
	void handleEvents(sf::RenderWindow &window, const sf::Event &event);
	void Update(sf::RenderWindow &window);
	void Compose(sf::RenderWindow &window);
};