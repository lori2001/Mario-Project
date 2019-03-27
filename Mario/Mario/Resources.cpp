#include "Resources.h"

sf::Texture Resources::loadingscreenT;
sf::Sprite Resources::loadingscreenS;

sf::Texture Resources::mario_small;

void Resources::loadFiles(sf::RenderWindow & window)
{
	loadingscreenT.loadFromFile("assets/images/loading.jpg");
	loadingscreenS.setTexture(loadingscreenT);

	window.clear();
	window.draw(loadingscreenS);
	window.display();

	mario_small.loadFromFile("assets/images/mario_small.png");
}
