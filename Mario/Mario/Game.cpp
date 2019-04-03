#include "Game.h"

void Game::Setup(sf::RenderWindow & window)
{
	clock.restart();
	mario.setPosition({ 110, 300 });

	ground1.setPosition({ 0, (float)HEIGHT - 150 });
	ground3.setPosition({ 400, (float)HEIGHT - 400 });

	enemy1.setPosition({ 400, 400 });
	enemy2.setPosition({ 600, 300});
}

void Game::Update(sf::RenderWindow & window)
{
	// Resets clock and stopwatches timer each frame
	elapsedTime = clock.getElapsedTime().asSeconds();
	clock.restart();

	// controls mario based on gravity and elapsed time
	mario.controls(elapsedTime, gravity);
	mario.animate(elapsedTime);

	mario.collidesWith(ground1.getGlobalBounds());
	mario.collidesWith(ground3.getGlobalBounds());

	enemy1.movement(elapsedTime, gravity);
	enemy1.animate(elapsedTime);
	enemy1.collidesWith(ground1.getGlobalBounds());
	enemy1.collidesWith(ground3.getGlobalBounds());
	enemy1.killorDie(mario);

	enemy2.movement(elapsedTime, gravity);
	enemy2.animate(elapsedTime);
	enemy2.collidesWith(ground1.getGlobalBounds());
	enemy2.collidesWith(ground3.getGlobalBounds());
	enemy2.killorDie(mario);
}

void Game::Compose(sf::RenderWindow & window) const
{
	window.draw(ground1);
	window.draw(ground3);
	window.draw(enemy1);
	window.draw(enemy2);
	window.draw(mario); // mario should always be the last
}
