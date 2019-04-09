#include "Game.h"

void Game::Setup(sf::RenderWindow & window)
{
	clock.restart();
	mario.initializeIn({ 110, 300 });

	luigi.changeCntrlKeys(sf::Keyboard::W,
		sf::Keyboard::S,
		sf::Keyboard::A,
		sf::Keyboard::D);
	luigi.changeTexture(Resources::luigi_smallT);
	luigi.initializeIn({ 800, 500 });

	ground1.setPosition({ 0, (float)HEIGHT - 150 });
	ground3.setPosition({ 400, (float)HEIGHT - 400 });

	enemy1.initializeIn({ 400, 400 });
	enemy2.initializeIn({ 600, 300});
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

	enemy2.movement(elapsedTime, gravity);
	enemy2.brickCol(ground1.getGlobalBounds());
	enemy2.brickCol(ground3.getGlobalBounds());
	enemy2.charCol(mario);
	enemy2.charCol(luigi);

	if (!mario.getlifeSignal() && !luigi.getlifeSignal()) {
		isActive = false;
	}
}

void Game::Compose(sf::RenderWindow & window) const
{
	window.draw(ground1);
	window.draw(ground3);
	window.draw(enemy1);
	window.draw(enemy2);

	// these should be last
	window.draw(mario);
	window.draw(luigi);
}
