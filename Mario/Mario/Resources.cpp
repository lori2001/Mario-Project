#include "Resources.h"

sf::Texture Resources::loadingscreenT;
sf::Sprite Resources::loadingscreenS;

sf::Texture Resources::mario_standT;
sf::Texture Resources::mario_walkT;

void Resources::loadFiles(sf::RenderWindow & window)
{
	loadingscreenT.loadFromFile("assets/images/loading.jpg");
	loadingscreenS.setTexture(loadingscreenT);

	window.clear();
	window.draw(loadingscreenS);
	window.display();

	mario_standT.loadFromFile("assets/images/mario_stand.png");
	mario_walkT.loadFromFile("assets/images/mario_walk.png");
}
