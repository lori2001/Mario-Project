#include "Resources.h"

sf::Texture Resources::loadingscreenT;
sf::Sprite Resources::loadingscreenS;

sf::Texture Resources::marioT;

void Resources::loadFiles(sf::RenderWindow & window)
{
	loadingscreenT.loadFromFile("assets/images/loading.jpg");
	loadingscreenS.setTexture(loadingscreenT);

	window.clear();
	window.draw(loadingscreenS);
	window.display();

	marioT.loadFromFile("assets/images/mario_front.png");
}
