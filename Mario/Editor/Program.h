#pragma once
#include <SFML/Graphics.hpp>
#include "Resources.h"
#include "UserInterface.h"
#include "Editor.h"

// Program creat pentru IBSA 2019 de Szoke Andras Lorand

class Program {
private:
	UserInterface userInterface;
	Editor editor;

	sf::View view{ sf::FloatRect{0, 0, WIDTH, HEIGHT} }; // scales sprites to window's size and moves cam when needed
public:
	// replaces int main()
	int run(sf::RenderWindow &window);
};