#include "Menu.h"

void Menu::Setup(sf::RenderWindow & window)
{
	startgame.setPosition({ WIDTH / 2 - startgame.getGlobalBounds().width / 2 , HEIGHT / 2 - 50 });
	exitgame.setPosition({ WIDTH / 2 - startgame.getGlobalBounds().width / 2 , HEIGHT / 2 + 50 });
}

void Menu::handleEvents(sf::RenderWindow & window, const sf::Event & event)
{
	mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window)); //gets mouse position relative to window

	startgame.selectByMouse(event, mouse);
	exitgame.selectByMouse(event, mouse);
}

void Menu::Update(sf::RenderWindow & window)
{
	if (startgame.activated()) {
		isActive = false;
	}
	if (exitgame.activated()) {
		window.close();
	}
}

void Menu::Compose(sf::RenderWindow & window)
{
	window.draw(startgame);
	window.draw(exitgame);
}
