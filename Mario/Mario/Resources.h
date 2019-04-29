#pragma once
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include <iostream>

// There is still no proper level-based resource management
// You should do it someday... :D

// Contains the viewport sizes, but this should not ever change
constexpr float WIDTH = 1920;
constexpr float HEIGHT = 1080;

class Resources {
private:
	static sf::Texture loadingscreenT;
	static sf::Sprite loadingscreenS;
	
	template <class Loadable>
	static void loadFile(Loadable &texture, const std::string & from);
	//static void loadFile(sf::Music & music, const std::string & from);
public:
	static sf::Image icon; // will hold icon file

	static sf::Texture menu_bgT;

	static sf::Texture heartT;
	static sf::Texture mario_smallT;
	static sf::Texture luigi_smallT;
	static sf::Texture enemy_mushT;
	static sf::Texture good_mushT;
	static sf::Texture groundT;
	static sf::Texture brickT;

	static sf::Music themesongM;

	static sf::Font super_marioF;

	// Load all files and display a loading screen while doing so
	static void loadFiles(sf::RenderWindow & window);
};

/* These stay in the .h file as suggested by Visual Studio*/
template<class Loadable>
inline void Resources::loadFile(Loadable & loadable, const std::string & from)
{
	if (!loadable.loadFromFile(from))
		std::cout << "error: could not load file from " << from << std::endl;
}
/*
void Resources::loadFile(sf::Music & music, const std::string & from)
{
	if (!music.openFromFile(from))
		std::cout << "error: could not load file from " << from << std::endl;
}*/
