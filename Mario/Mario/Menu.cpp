#include "Menu.h"

void Menu::Setup(sf::RenderWindow & window)
{
	startgame.setPosition({ WIDTH / 2 - startgame.getGlobalBounds().width / 2 , HEIGHT / 2 - 50 });
	exitgame.setPosition({ WIDTH / 2 - startgame.getGlobalBounds().width / 2 , HEIGHT / 2 + 50 });
}

void Menu::handleEvents(sf::RenderWindow & window, const sf::Event & event)
{
	mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window)); //gets mouse position relative to window

	/* count the number of relevant keypresses*/
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		arrowCount++;
		if (arrowCount > 1) { arrowCount = 0; } // max limit
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		arrowCount--;
		if (arrowCount < 0) { arrowCount = 1; } // min limit
	}

	startgame.selectByKeyboard(1, arrowCount);
	exitgame.selectByKeyboard(0, arrowCount);

	startgame.handleEvents(event);
	exitgame.handleEvents(event);
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
