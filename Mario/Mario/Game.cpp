#include "Game.h"

void Game::Setup(sf::RenderWindow & window)
{
	mario.setPosition({ 110, 300 });

	ground1.setPosition({ 100, (float)HEIGHT - 150 });
//	ground2.setPosition({ 400, (float)HEIGHT - 350 });
	ground3.setPosition({ 400, (float)HEIGHT - 250 });
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
//	mario.collidesWith(ground2.getGlobalBounds());
	mario.collidesWith(ground3.getGlobalBounds());
}

void Game::Compose(sf::RenderWindow & window) const
{
	window.draw(mario);
	window.draw(ground1);
//	window.draw(ground2);
	window.draw(ground3);
}
