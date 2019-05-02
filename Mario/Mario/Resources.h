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
public:
	// Load all files and display a loading screen while doing so
	static void loadFiles(sf::RenderWindow & window);
private:
	template <class Loadable>
	static void loadFile(Loadable &texture, const std::string & from);
public:
	static sf::Texture menu_bgT; // the background of the menu

	static sf::Texture heartT;
	static sf::Texture mario_smallT;
	static sf::Texture luigi_smallT;
	static sf::Texture enemy_mushT;
	static sf::Texture good_mushT;
	static sf::Texture coinT;
	static sf::Texture castle_smallT;
	static sf::Texture flagT;

	static sf::Texture groundT;
	static sf::Texture brickT;

	static sf::Font super_marioF;

	static sf::SoundBuffer coinSB;
	static sf::SoundBuffer jumpSB;
	static sf::SoundBuffer bumpSB;
	static sf::SoundBuffer stompSB;
	static sf::SoundBuffer kickSB;

	static sf::Music themesongM;
	static sf::Music stageClearM;
	static sf::Music worldClearM;
	static sf::Music gameoverM;
	static void stopAllSongs();
};

/* These stay in the .h file as suggested by Visual Studio*/
template<class Loadable>
inline void Resources::loadFile(Loadable & loadable, const std::string & from)
{
	if (!loadable.loadFromFile(from))
		std::cout << "ERROR: could not load file from " << from << std::endl;
}
