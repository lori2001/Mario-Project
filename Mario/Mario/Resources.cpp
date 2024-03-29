#include "Resources.h"

sf::Texture Resources::menu_bgT;
sf::Texture Resources::sceneryT;

sf::Texture Resources::heartT;
sf::Texture Resources::luigi_smallT;
sf::Texture Resources::mario_smallT;
sf::Texture Resources::enemy_mushT;
sf::Texture Resources::good_mushT;
sf::Texture Resources::coinT;
sf::Texture Resources::castle_smallT;
sf::Texture Resources::flagT;

sf::Texture Resources::groundT;
sf::Texture Resources::brickT;

sf::Font Resources::super_marioF;

sf::SoundBuffer Resources::coinSB;
sf::SoundBuffer Resources::jumpSB;
sf::SoundBuffer Resources::bumpSB;
sf::SoundBuffer Resources::stompSB;
sf::SoundBuffer Resources::kickSB;

sf::Music Resources::themesongM;
sf::Music Resources::stageClearM;
sf::Music Resources::worldClearM;
sf::Music Resources::gameoverM;

void Resources::loadFiles(sf::RenderWindow & window)
{
	sf::Texture loadingscreenT;
	sf::Sprite loadingscreenS;

	// loads loadingscreen
	loadFile(loadingscreenT, "assets/images/loading.jpg");
	loadingscreenS.setTexture(loadingscreenT);

	// scales loading image to window's size (because the view is not applied yet)
	loadingscreenS.setScale(float(window.getSize().x) / float(loadingscreenT.getSize().x), float(window.getSize().y) / float(loadingscreenT.getSize().y));

	// draws loadingscreen
	window.clear();
	window.draw(loadingscreenS);
	window.display();

	// loads all files
	loadFile(menu_bgT, "assets/images/menu_bg.jpg");
	loadFile(sceneryT, "assets/images/scenery.png");

	loadFile(heartT, "assets/images/heart.png");
	loadFile(luigi_smallT, "assets/images/luigi_small.png");
	loadFile(mario_smallT, "assets/images/mario_small.png");
	loadFile(enemy_mushT, "assets/images/enemy_mush.png");
	loadFile(good_mushT, "assets/images/good_mush.png");
	loadFile(coinT, "assets/images/coin.png");
	loadFile(castle_smallT, "assets/images/castle_small.png");
	loadFile(flagT, "assets/images/flag.png");

	loadFile(groundT, "assets/images/ground.png");
	loadFile(brickT, "assets/images/brick.png");

	loadFile(super_marioF, "assets/fonts/super_mario.ttf");

	loadFile(coinSB, "assets/audio/coin.wav");
	loadFile(jumpSB, "assets/audio/jump.wav");
	loadFile(bumpSB, "assets/audio/bump.wav");
	loadFile(stompSB, "assets/audio/stomp.wav");
	loadFile(kickSB, "assets/audio/kick.wav");

	// music files need another type of loading
	if (!themesongM.openFromFile("assets/audio/theme.wav")) {
		std::cout << "ERROR: could not load file from assets/audio/theme.wav" << std::endl;
	}
	themesongM.setLoop(true);

	if (!gameoverM.openFromFile("assets/audio/gameover.wav")) {
		std::cout << "ERROR: could not load file from assets/audio/gameover.wav" << std::endl;
	}
	if (!stageClearM.openFromFile("assets/audio/stage_clear.wav")) {
		std::cout << "ERROR: could not load file from assets/audio/stage_clear.wav" << std::endl;
	}
	if (!worldClearM.openFromFile("assets/audio/world_clear.wav")) {
		std::cout << "ERROR: could not load file from assets/audio/world_clear.wav" << std::endl;
	}

	/*Lehalkitas*/
	themesongM.setVolume(10);
	stageClearM.setVolume(10);
	worldClearM.setVolume(10);
	gameoverM.setVolume(10);
}

void Resources::stopAllSongs()
{
	themesongM.stop();
	gameoverM.stop();
	worldClearM.stop();
	stageClearM.stop();
}
