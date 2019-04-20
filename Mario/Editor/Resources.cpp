#include "Resources.h"

sf::Texture Resources::loadingscreenT;
sf::Sprite Resources::loadingscreenS;

sf::Texture Resources::open_iconT;
sf::Texture Resources::save_iconT;

sf::Texture Resources::heartT;
sf::Texture Resources::luigi_smallT;
sf::Texture Resources::mario_smallT;
sf::Texture Resources::enemy_mushT;
sf::Texture Resources::good_mushT;
sf::Texture Resources::groundT;
sf::Texture Resources::brickT;

sf::Font Resources::super_marioF;

void Resources::loadFiles(sf::RenderWindow & window)
{
	std::cout << "Loading Files..." << std::endl;

	// loads loadingscreen
	loadFile(loadingscreenT, Paths::getGamePath() + "\\assets\\images\\loading.jpg");
	loadingscreenS.setTexture(loadingscreenT);

	// scales loading image to window's size
	loadingscreenS.setScale(float(window.getSize().x) / float(loadingscreenT.getSize().x), float(window.getSize().y) / float(loadingscreenT.getSize().y));

	// draws loadingscreen
	window.clear();
	window.draw(loadingscreenS);
	window.display();

	loadFile(open_iconT, "assets\\images\\open_icon.png");
	loadFile(save_iconT, "assets\\images\\save_icon.png");

	loadFile(heartT, Paths::getGamePath() + "\\assets\\images\\heart.png");
	loadFile(luigi_smallT, Paths::getGamePath() + "\\assets\\images\\luigi_small.png");
	loadFile(mario_smallT, Paths::getGamePath() + "\\assets\\images\\mario_small.png");
	loadFile(enemy_mushT, Paths::getGamePath() + "\\assets\\images\\enemy_mush.png");
	loadFile(good_mushT, Paths::getGamePath() + "\\assets\\images\\good_mush.png");

	loadFile(brickT, Paths::getGamePath() + "\\assets\\images\\brick.png");
	loadFile(groundT, Paths::getGamePath() + "\\assets\\images\\ground.png");

	loadFile(super_marioF, Paths::getGamePath() + "\\assets\\fonts\\super_mario.ttf");

	std::cout << "All Files Loaded!" << std::endl;
}
