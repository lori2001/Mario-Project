#pragma once
#include "SFML/Graphics.hpp"
#include "Resources.h"
#include "Button.h"

class MainMenu {
private:
	sf::Vector2f mouse; // holds position of the mouse
	sf::Sprite background{ Resources::menu_bgT }; // sprite for the background duh...

	UI::Button startgame{ Resources::super_marioF, "Start Game", {600, 75} };
	UI::Button exitgame{ Resources::super_marioF, "Exit", {600, 75}};

public:

	void Setup(sf::RenderWindow &window);
	void handleEvents(sf::RenderWindow &window, const sf::Event &event);
	void Update(sf::RenderWindow &window, bool& isActive);
	void Compose(sf::RenderWindow &window);
};