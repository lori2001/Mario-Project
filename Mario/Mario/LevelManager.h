#pragma once
#include <SFML/Graphics.hpp>
#include "Resources.h"
#include "MainMenu.h"
#include "Game.h"
#include "Maps.h"
#include "Endscreen.h"

// Program creat pentru IBSA 2019 de Szoke Andras Lorand

class LevelManager {
private:
	sf::View view{ sf::FloatRect{0, 0, 1920, 1080} }; // scales sprites to window's size and moves cam when needed

	Game game;
	MainMenu mainmenu;
	Endscreen endscreen;
public:
	// replaces int main()
	int run(sf::RenderWindow &window);
};