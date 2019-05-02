#include "Gamewon.h"

void Gamewon::Setup(sf::RenderWindow & window, const bool worldWon)
{
	goBack.setPosition({ 100 ,900 });
	goOn.setPosition({ 1320 ,900 });

	goBack.setFillColor(sf::Color::White);
	goOn.setFillColor(sf::Color::White);
	goBack.setTextColor(sf::Color::Black);
	goOn.setTextColor(sf::Color::Black);

	score.updateString();
	score.setCharacterSize(100);

	gameWon.setCharacterSize(180);

	// stop all songs
	Resources::stopAllSongs();

	if (worldWon) {
		// change string a little
		gameWon.setString("GAME WON!");
		// play music
		Resources::worldClearM.play();
		// display the total score throughout the world
		Score::equal(Score::getTotal());
		gameWon.setCharacterSize(200);

		// just make sure go on button can't be reached
		goOn.setFillColor(sf::Color::Transparent);
		goOn.setPosition({-9999.99f, -9999.99f});

		// place in middle instead
		goBack.setPosition({ WIDTH / 2 - goBack.getGlobalBounds().width / 2 ,900 });
	}

	// these have to be set anyway
	score.setPosition(WIDTH / 2 - score.getGlobalBounds().width / 2, 500);
	gameWon.setPosition(WIDTH / 2 - gameWon.getGlobalBounds().width / 2, 175);

	isActive = true;
}

void Gamewon::handleEvents(const sf::RenderWindow & window, const sf::Event & event)
{
	mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window)); //gets mouse position relative to window

	goBack.selectByMouse(mouse);
	goOn.selectByMouse(mouse);

	goBack.handleEvents(event);
	goOn.handleEvents(event);
}

void Gamewon::Update(sf::RenderWindow & window)
{
	if (goOn.activated()) {
		isActive = false;
		cont = true;
	}
	else if (goBack.activated()) {
		isActive = false;
		cont = false;
	}
}

void Gamewon::Compose(sf::RenderWindow & window)
{
	window.draw(gameWon);
	window.draw(goBack);
	window.draw(goOn);
	window.draw(score);
}
