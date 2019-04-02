#include "Resources.h"

sf::Texture Resources::loadingscreenT;
sf::Sprite Resources::loadingscreenS;

sf::Texture Resources::menu_bgT;
sf::Texture Resources::mario_smallT;
sf::Texture Resources::enemyT;
sf::Texture Resources::groundT;

sf::Font Resources::super_marioF;

sf::Image Resources::icon;

void Resources::loadFiles(sf::RenderWindow & window)
{
	// loads loadingscreen
	loadFile(loadingscreenT, "assets/images/loading.jpg");
	loadingscreenS.setTexture(loadingscreenT);

	// scales loading image to window's size
	loadingscreenS.setScale(float(window.getSize().x) / float(loadingscreenT.getSize().x), float(window.getSize().y) / float(loadingscreenT.getSize().y));

	// draws loadingscreen
	window.clear();
	window.draw(loadingscreenS);
	window.display();

	// loads all files
	loadFile(icon, "icon.png");

	loadFile(menu_bgT, "assets/images/menu_bg.jpg");

	loadFile(mario_smallT, "assets/images/mario_small.png");
	loadFile(enemyT, "assets/images/enemy.png");

	loadFile(groundT, "assets/images/ground.png");
	groundT.setRepeated(true);

	loadFile(super_marioF, "assets/fonts/super_mario.ttf");
}
