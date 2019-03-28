#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

// There is still no proper level-based resource management
// You should do it someday... :D

// Contains the viewport sizes, but this should not ever change
constexpr int WIDTH = 1920;
constexpr int HEIGHT = 1080;

class Resources {
private:
	static sf::Texture loadingscreenT;
	static sf::Sprite loadingscreenS;
	
	template <class Loadable>
	static void loadFile(Loadable &texture, const std::string & from);
public:
	static sf::Texture mario_smallT;
	static sf::Texture groundT;

	// Load all files and display a loading screen while doing so
	static void loadFiles(sf::RenderWindow & window);
};

template<class Loadable>
inline void Resources::loadFile(Loadable & loadable, const std::string & from)
{
	if (!loadable.loadFromFile(from))
		std::cout << "error: could not load file from " << from << std::endl;
}
