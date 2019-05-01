#include "Resources.h"

sf::Texture Resources::open_iconT;
sf::Texture Resources::save_iconT;

sf::Texture Resources::heartT;
sf::Texture Resources::luigi_smallT;
sf::Texture Resources::mario_smallT;
sf::Texture Resources::enemy_mushT;
sf::Texture Resources::good_mushT;
sf::Texture Resources::coinT;
sf::Texture Resources::castle_smallT;

sf::Texture Resources::groundT;
sf::Texture Resources::brickT;

sf::Font Resources::super_marioF;

bool Resources::loadFiles(sf::RenderWindow & window)
{
	std::cout << "Loading Files..." << std::endl;

	/* LOAD AND DISPLAY LOADINGSCREEN START */

	sf::Texture loadingscreenT;
	sf::Sprite loadingscreenS;

	// use this texture loading to check if there is a properly set up assets folder
	if (!loadingscreenT.loadFromFile(Paths::getGamePath() + "assets\\images\\loading.jpg")) {
		return false;
	}
	loadingscreenS.setTexture(loadingscreenT);

	// scales loading image to window's size
	loadingscreenS.setScale(float(window.getSize().x) / float(loadingscreenT.getSize().x), float(window.getSize().y) / float(loadingscreenT.getSize().y));

	// draws loadingscreen
	window.clear();
	window.draw(loadingscreenS);
	window.display();

	/* LOAD AND DISPLAY LOADINGSCREEN END */

	loadFile(open_iconT, "assets\\images\\open_icon.png");
	loadFile(save_iconT, "assets\\images\\save_icon.png");

	loadFile(heartT, Paths::getGamePath() + "assets\\images\\heart.png");
	loadFile(luigi_smallT, Paths::getGamePath() + "assets\\images\\luigi_small.png");
	loadFile(mario_smallT, Paths::getGamePath() + "assets\\images\\mario_small.png");
	loadFile(enemy_mushT, Paths::getGamePath() + "assets\\images\\enemy_mush.png");
	loadFile(good_mushT, Paths::getGamePath() + "assets\\images\\good_mush.png");
	loadFile(coinT, Paths::getGamePath() + "assets\\images\\coin.png");
	loadFile(castle_smallT, Paths::getGamePath() + "assets\\images\\castle_small.png");

	loadFile(groundT, Paths::getGamePath() + "assets\\images\\ground.png");
	groundT.setRepeated(true);
	loadFile(brickT, Paths::getGamePath() + "assets\\images\\brick.png");
	brickT.setRepeated(true);

	loadFile(super_marioF, Paths::getGamePath() + "assets\\fonts\\super_mario.ttf");

	std::cout << "All Files Loaded!" << std::endl;

	return true;
}
