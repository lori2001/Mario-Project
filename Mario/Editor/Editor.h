#pragma once
#include <SFML/Graphics.hpp>
#include "Resources.h"

// Program creat pentru IBSA 2019 de Szoke Andras Lorand

class Editor {
private:
	sf::View view{ sf::FloatRect{0, 0, 1920, 1080} }; // scales sprites to window's size and moves cam when needed
public:
	// replaces int main()
	int run(sf::RenderWindow &window);
};