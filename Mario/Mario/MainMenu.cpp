#include "MainMenu.h"

void MainMenu::Setup()
{
	// play the themesong (stop other songs)
	Resources::stopAllSongs();
	Resources::themesongM.play();

	startgame.setPosition({ WIDTH / 2 - startgame.getGlobalBounds().width / 2 , HEIGHT / 2 - 50 });
	exitgame.setPosition({ WIDTH / 2 - startgame.getGlobalBounds().width / 2 , HEIGHT / 2 + 70 });
	startgame.setCharacterSize(50);
	exitgame.setCharacterSize(50);

	// if menu is initialized, game didn't start yet
	startGame = false;
}

void MainMenu::handleEvents(const sf::RenderWindow & window, const sf::Event & event)
{
	mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window)); //gets mouse position relative to window

	startgame.selectByMouse(mouse);
	exitgame.selectByMouse(mouse);

	startgame.handleEvents(event);
	exitgame.handleEvents(event);
}

void MainMenu::Update(sf::RenderWindow & window)
{
	if (startgame.activated()) {
		startGame = true;
	}
	if (exitgame.activated()) {
		window.close();
	}
}

void MainMenu::Compose(sf::RenderWindow & window)
{
	window.draw(background);
	window.draw(startgame);
	window.draw(exitgame);
}
