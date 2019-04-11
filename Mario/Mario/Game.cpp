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

	ground1.initializeIn(19, { 0, (float)HEIGHT - 150 });
	brick.initializeIn(8, { 400, (float)HEIGHT - 400 });

	enemy.initializeIn({ 400, 400 });
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

	mario.groundCol(ground1);
	mario.groundCol(brick);
	luigi.groundCol(ground1);
	luigi.groundCol(brick);

	enemy.movement(elapsedTime, gravity);
	enemy.animate(elapsedTime);
	enemy.groundCol(ground1);
	enemy.groundCol(brick);
	enemy.charCol(mario);
	enemy.charCol(luigi);

	brick.animate(elapsedTime);
	
	healer.movement(elapsedTime, gravity);
	healer.groundCol(ground1);
	healer.groundCol(brick);
	healer.charCol(mario);
	healer.charCol(luigi);

	if (!mario.getlifeSignal() && !luigi.getlifeSignal()) {
		isActive = false;
	}
}

void Game::Compose(sf::RenderWindow & window) const
{
	window.draw(ground1);
	window.draw(brick);
	window.draw(enemy);
	window.draw(healer);

	// these should be last
	window.draw(mario);
	window.draw(luigi);
}
