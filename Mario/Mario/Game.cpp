#include "Game.h"

void Game::Setup(sf::RenderWindow & window)
{
	clock.restart();
	mario1.setPosition({ 110, 300 });

	mario2.changeCntrlKeys(sf::Keyboard::W,
		sf::Keyboard::S,
		sf::Keyboard::A,
		sf::Keyboard::D);
	mario2.changeTexture(Resources::luigi_smallT);
	mario2.setPosition({ 800, 500 });

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
	mario1.controls(elapsedTime, gravity);
	mario1.animate(elapsedTime);

	mario2.controls(elapsedTime, gravity);
	mario2.animate(elapsedTime);

	mario1.collidesWith(ground1.getGlobalBounds());
	mario1.collidesWith(ground3.getGlobalBounds());
	mario2.collidesWith(ground1.getGlobalBounds());
	mario2.collidesWith(ground3.getGlobalBounds());

	enemy1.movement(elapsedTime, gravity);
	enemy1.animate(elapsedTime);
	enemy1.collidesWith(ground1.getGlobalBounds());
	enemy1.collidesWith(ground3.getGlobalBounds());
	enemy1.killorDie(mario1);
	enemy1.killorDie(mario2);

	enemy2.movement(elapsedTime, gravity);
	enemy2.animate(elapsedTime);
	enemy2.collidesWith(ground1.getGlobalBounds());
	enemy2.collidesWith(ground3.getGlobalBounds());
	enemy2.killorDie(mario1);
	enemy2.killorDie(mario2);
}

void Game::Compose(sf::RenderWindow & window) const
{
	window.draw(ground1);
	window.draw(ground3);
	window.draw(enemy1);
	window.draw(enemy2);
	window.draw(mario1); // mario should always be the last
	window.draw(mario2); // mario should always be the last
}
