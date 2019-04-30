#include "Endscreen.h"

void Endscreen::Setup(sf::RenderWindow & window)
{
	goback.setPosition({ 100 ,900 });
	exit.setPosition({ 1320 ,900 });

	goback.setFillColor(sf::Color::White);
	exit.setFillColor(sf::Color::White);
	goback.setTextColor(sf::Color::Black);
	exit.setTextColor(sf::Color::Black);

	score.updateString();
	score.setCharacterSize(100);
	score.setPosition(WIDTH / 2 - score.getGlobalBounds().width / 2, 500);

	gameover.setPosition(WIDTH / 2 - gameover.getGlobalBounds().width / 2, 175);

	// play gameover (stop other songs)
	Resources::themesongM.stop();
	Resources::gameoverM.play();
}

void Endscreen::handleEvents(const sf::RenderWindow & window, const sf::Event & event)
{
	mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window)); //gets mouse position relative to window

	goback.selectByMouse(mouse);
	exit.selectByMouse(mouse);

	goback.handleEvents(event);
	exit.handleEvents(event);
}

void Endscreen::Update(sf::RenderWindow & window)
{
	if (exit.activated()) {
		window.close();
	}
	else if (goback.activated()) {
		isActive = false;
	}
}

void Endscreen::Compose(sf::RenderWindow & window)
{
	window.draw(gameover);
	window.draw(goback);
	window.draw(exit);
	window.draw(score);
}
