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

	score.setPosition({1620,20});
	score.equal(0);

	// eliminates potential bugs on trashware
	clock.restart();
}

void Game::Update(sf::RenderWindow & window, bool& isActive)
{
	// Resets clock and stopwatches timer each frame
	elapsedTime = clock.getElapsedTime().asSeconds();
	clock.restart();

	mario.movement(elapsedTime, gravity);
	mario.animation(elapsedTime);
	mario.collision(ground1);
	mario.collision(brick);

	luigi.movement(elapsedTime, gravity);
	luigi.animation(elapsedTime);
	luigi.collision(ground1);
	luigi.collision(brick);

	enemy.movement(elapsedTime, gravity);
	enemy.animation(elapsedTime);
	enemy.collision(ground1);
	enemy.collision(brick);
	enemy.collision(mario);
	enemy.collision(luigi);

	brick.animation(elapsedTime);
	
	healer.movement(elapsedTime, gravity);
	healer.collision(ground1);
	healer.collision(brick);
	healer.collision(mario);
	healer.collision(luigi);

	if (!mario.getlifeSignal() && !luigi.getlifeSignal()) {
		isActive = false;
	}

	score.updateString();
}

void Game::Compose(sf::RenderWindow & window) const
{
	window.draw(ground1);
	window.draw(brick);
	window.draw(enemy);
	window.draw(healer);

	window.draw(mario);
	window.draw(luigi);

	window.draw(score);
}
