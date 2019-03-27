#pragma once
#include "SFML/Graphics.hpp"

// There is still no proper level-based resource management
// You should do it someday... :D

// Contains the viewport sizes, but this should not ever change
constexpr int WIDTH = 1920;
constexpr int HEIGHT = 1080;

class Resources {
private:
	static sf::Texture loadingscreenT;
	static sf::Sprite loadingscreenS;

public:
	static sf::Texture mario_small;

	// Load all files and display a loading screen while doing so
	static void loadFiles(sf::RenderWindow & window);
};