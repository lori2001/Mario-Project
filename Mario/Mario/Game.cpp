#include "Game.h"

void Game::Setup(sf::RenderWindow & window)
{
	mario.initializeIn({ 1400, 500 });

	luigi.changeCntrlKeys(sf::Keyboard::W,
		sf::Keyboard::S,
		sf::Keyboard::A,
		sf::Keyboard::D);
	luigi.changeTexture(Resources::luigi_smallT);
	luigi.changeHeartsPos({20,60});
	luigi.initializeIn({ 700, 800 });

	ground1.setPosition({ 0, (float)HEIGHT - 150 });
	ground3.setPosition({ 400, (float)HEIGHT - 400 });

	enemy1.initializeIn({ 400, 400 });
	healer.initializeIn({ 600, 300});

	// eliminates potential bugs on trashware
	clock.restart();
}

void Game::Update(sf::RenderWindow & window, bool& isActive)
{
	// Resets clock and stopwatches timer each frame
	elapsedTime = clock.getElapsedTime().asSeconds();
	clock.restart();

	// controls mario based on gravity and elapsed time
	mario.controls(elapsedTime, gravity);
	mario.animate(elapsedTime);

	luigi.controls(elapsedTime, gravity);
	luigi.animate(elapsedTime);

	mario.brickCol(ground1.getGlobalBounds());
	mario.brickCol(ground3.getGlobalBounds());
	luigi.brickCol(ground1.getGlobalBounds());
	luigi.brickCol(ground3.getGlobalBounds());

	enemy1.movement(elapsedTime, gravity);
	enemy1.animate(elapsedTime);
	enemy1.brickCol(ground1.getGlobalBounds());
	enemy1.brickCol(ground3.getGlobalBounds());
	enemy1.charCol(mario);
	enemy1.charCol(luigi);

	healer.movement(elapsedTime, gravity);
	healer.brickCol(ground1.getGlobalBounds());
	healer.brickCol(ground3.getGlobalBounds());
	healer.charCol(mario);
	healer.charCol(luigi);

	if (!mario.getlifeSignal() && !luigi.getlifeSignal()) {
		isActive = false;
	}
}

void Game::Compose(sf::RenderWindow & window) const
{
	window.draw(ground1);
	window.draw(ground3);
	window.draw(enemy1);
	window.draw(healer);

	// these should be last
	window.draw(mario);
	window.draw(luigi);
}
