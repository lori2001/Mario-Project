#include "MainMenu.h"

void MainMenu::Setup(sf::RenderWindow & window)
{
	startgame.setPosition({ WIDTH / 2 - startgame.getGlobalBounds().width / 2 , HEIGHT / 2 - 50 });
	exitgame.setPosition({ WIDTH / 2 - startgame.getGlobalBounds().width / 2 , HEIGHT / 2 + 70 });
	startgame.setCharacterSize(50);
	exitgame.setCharacterSize(50);
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
		isActive = false;
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
