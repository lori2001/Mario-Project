#include "Game.h"

void Game::Setup(sf::RenderWindow & window)
{
	score.setPosition({ 1620,20 }); // set display position
	score.equal(0); // reset score if needed
	
	/* Load in game info into actual game elements*/

	luigi.changeCntrlKeys(sf::Keyboard::W,
		sf::Keyboard::S,
		sf::Keyboard::A,
		sf::Keyboard::D);
	luigi.changeTexture(Resources::luigi_smallT);
	luigi.changeHeartsPos({ 20,60 });

	mario.initializeIn(Maps::getCharacter1());
	luigi.initializeIn(Maps::getCharacter2());

	if (Maps::getCharacter1().x == notfound && Maps::getCharacter1().y == notfound) {
		mario.doNotDisplay();
	}
	if (Maps::getCharacter2().x == notfound && Maps::getCharacter2().y == notfound) {
		luigi.doNotDisplay();
	}

	for (int i = 0; i < Maps::getEnemiesNum(); i++) {
		if (i >= int(enemies.size())) enemies.push_back(Enemy{ Maps::getEnemy(i) });
		else enemies[i].initializeIn(Maps::getEnemy(i));
	}
	for (int i = 0; i < Maps::getHealersNum(); i++) {
		if (i >= int(healers.size())) healers.push_back(Healer{ Maps::getHealer(i) });
		else healers[i].initializeIn(Maps::getHealer(i));
	}
	for (int i = 0; i < Maps::getBricksNum(); i++) {
		if (i >= int(bricks.size())) bricks.push_back(Brick{ Maps::getBrick(i) });
		else bricks[i].initializeIn(Maps::getBrick(i));
	}
	for (int i = 0; i < Maps::getGroundsNum(); i++) {
		if (i >= int(grounds.size())) grounds.push_back(Ground{ Maps::getGround(i) });
		else grounds[i].initializeIn(Maps::getGround(i));
	}

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

	luigi.movement(elapsedTime, gravity);
	luigi.animation(elapsedTime);

	for (int i = 0; i < Maps::getGroundsNum(); i++) {
		mario.collision(grounds[i]);
		luigi.collision(grounds[i]);
	}
	for (int i = 0; i < Maps::getBricksNum(); i++) {
		mario.collision(bricks[i]);
		luigi.collision(bricks[i]);
		bricks[i].animation(elapsedTime);
	}

	for (int i = 0; i < Maps::getEnemiesNum(); i++) {
		enemies[i].movement(elapsedTime, gravity);
		enemies[i].animation(elapsedTime);
		enemies[i].collision(mario);
		enemies[i].collision(luigi);

		for (int j = 0; j < Maps::getGroundsNum(); j++) {
			enemies[i].collision(grounds[j]);
		}
		for (int j = 0; j < Maps::getBricksNum(); j++) {
			enemies[i].collision(bricks[j]);
		}
	}

	for (int i = 0; i < Maps::getHealersNum(); i++) {
		healers[i].movement(elapsedTime, gravity);
		healers[i].collision(mario);
		healers[i].collision(luigi);

		for (int j = 0; j < Maps::getGroundsNum(); j++) {
			healers[i].collision(grounds[j]);
		}
		for (int j = 0; j < Maps::getBricksNum(); j++) {
			healers[i].collision(bricks[j]);
		}
	}

	if (!mario.getlifeSignal() && !luigi.getlifeSignal()) {
		isActive = false;
	}

	score.updateString();
}

void Game::Compose(sf::RenderWindow & window) const
{
	for (int i = 0; i < Maps::getGroundsNum(); i++) {
		window.draw(grounds[i]);
	}
	for (int i = 0; i < Maps::getBricksNum(); i++) {
		window.draw(bricks[i]);
	}
	for (int i = 0; i < Maps::getEnemiesNum(); i++) {
		window.draw(enemies[i]);
	}
	for (int i = 0; i < Maps::getHealersNum(); i++) {
		window.draw(healers[i]);
	}

	window.draw(mario);
	window.draw(luigi);

	window.draw(score);
}
