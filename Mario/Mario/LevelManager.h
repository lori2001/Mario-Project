#pragma once
#include <SFML/Graphics.hpp>
#include "Resources.h"
#include "MainMenu.h"
#include "Game.h"
#include "Maps.h"
#include "Gameover.h"
#include "Gamewon.h"

// Program creat pentru IBSA 2019 de Szoke Andras Lorand

class LevelManager {
private:
	sf::View view{ sf::FloatRect{0, 0, WIDTH, HEIGHT} }; // scales sprites to window's size and moves cam when needed

	Game game;
	MainMenu mainmenu;
	Gameover gameover;
	Gamewon gamewon;
public:
	// replaces int main()
	int run(sf::RenderWindow &window);
};