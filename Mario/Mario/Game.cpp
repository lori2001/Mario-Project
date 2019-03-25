#include "Game.h"

void Game::Setup(sf::RenderWindow & window)
{
	mario.setTexture(resources.marioT);
	mario.setScale(2.2f);
	mario.setPosition({ 100, 800 });
}

void Game::Update(sf::RenderWindow & window)
{
	// Resets clock and stopwatches timer each frame
	elapsedTime = clock.getElapsedTime().asSeconds();
	clock.restart();

	// controls mario based on gravity and elapsed time
	mario.controls(elapsedTime, gravity);

}

void Game::Compose(sf::RenderWindow & window) const
{
	window.draw(mario);
	window.draw(ground);
}
