#include "Game.h"

void Game::Setup(sf::RenderWindow & window)
{
	mario.setScale(2.2f);
	mario.setPosition({ 200, 500 });

	ground1.sprite.setFillColor(sf::Color::Yellow);
	ground1.sprite.setPosition({ 100, (float)HEIGHT - 150 });
	ground1.sprite.setSize({ (float)WIDTH - 150, 50 });

	ground2.sprite.setFillColor(sf::Color::Red);
	ground2.sprite.setPosition({ 400, (float)HEIGHT - 450 });
	ground2.sprite.setSize({ (float)WIDTH / 2, 50 });
}

void Game::Update(sf::RenderWindow & window)
{
	// Resets clock and stopwatches timer each frame
	elapsedTime = clock.getElapsedTime().asSeconds();
	clock.restart();

	// controls mario based on gravity and elapsed time
	mario.controls(elapsedTime, gravity);
	mario.collidesWith(ground1.getGlobalBounds());
	mario.collidesWith(ground2.getGlobalBounds());
}

void Game::Compose(sf::RenderWindow & window) const
{
	window.draw(mario);
	window.draw(ground1);
	window.draw(ground2);
}
