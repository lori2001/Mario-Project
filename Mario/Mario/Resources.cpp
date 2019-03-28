#include "Resources.h"

sf::Texture Resources::loadingscreenT;
sf::Sprite Resources::loadingscreenS;

sf::Texture Resources::mario_smallT;
sf::Texture Resources::groundT;

void Resources::loadFiles(sf::RenderWindow & window)
{
	loadFile(loadingscreenT, "assets/images/loading.jpg");
	loadingscreenS.setTexture(loadingscreenT);

	window.clear();
	window.draw(loadingscreenS);
	window.display();

	loadFile(mario_smallT, "assets/images/mario_small.png");

	loadFile(groundT, "assets/images/ground.png");
	groundT.setRepeated(true);
}
