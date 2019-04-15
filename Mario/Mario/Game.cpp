#include "Game.h"

void Game::Setup(sf::RenderWindow & window)
{
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

	enemies.clear();
	for (int i = 0; i < Maps::getEnemiesNum(); i++) {
		enemies.push_back(Enemy{ Maps::getEnemy(i) });
	}
	healers.clear();
	for (int i = 0; i < Maps::getHealersNum(); i++) {
		healers.push_back(Healer{ Maps::getHealer(i) });
	}
	bricks.clear();
	for (int i = 0; i < Maps::getBricksNum(); i++) {
		bricks.push_back(Brick{ Maps::getBrick(i) });
	}
	grounds.clear();
	for (int i = 0; i < Maps::getGroundsNum(); i++) {
		grounds.push_back(Ground{ Maps::getGround(i) });
	}

	// eliminates potential bugs on trashware
	clock.restart();
}

void Game::Update(const sf::RenderWindow & window, sf::View &view)
{
	// Resets clock and stopwatches timer each frame
	elapsedTime = clock.getElapsedTime().asSeconds();
	clock.restart();

	//  character can move and be moved by the view unlike other elements
	mario.movement(elapsedTime, gravity, view);
	mario.animation(elapsedTime);

	luigi.movement(elapsedTime, gravity, view);
	luigi.animation(elapsedTime);

	for (int i = 0; i < int(grounds.size()); i++) {
		mario.collision(grounds[i]);
		luigi.collision(grounds[i]);
	}
	for (int i = 0; i < int(bricks.size()); i++) {
		mario.collision(bricks[i]);
		luigi.collision(bricks[i]);
		bricks[i].animation(elapsedTime);
	}

	for (int i = 0; i < int(enemies.size()); i++) {
		enemies[i].movement(elapsedTime, gravity);
		enemies[i].animation(elapsedTime);
		enemies[i].collision(mario);
		enemies[i].collision(luigi);

		for (int j = 0; j < int(grounds.size()); j++) {
			enemies[i].collision(grounds[j]);
		}
		for (int j = 0; j < int(bricks.size()); j++) {
			enemies[i].collision(bricks[j]);
		}
	}

	for (int i = 0; i < int(healers.size()); i++) {
		healers[i].movement(elapsedTime, gravity);
		healers[i].collision(mario);
		healers[i].collision(luigi);

		for (int j = 0; j < int(grounds.size()); j++) {
			healers[i].collision(grounds[j]);
		}
		for (int j = 0; j < int(bricks.size()); j++) {
			healers[i].collision(bricks[j]);
		}
	}

	// check if mario and luigi are still alive and deactivate game if they are not
	if (!mario.getlifeSignal() && !luigi.getlifeSignal()) {
		isActive = false;
	}

	score.updateString();
	score.setPosition({ view.getCenter().x + 660, 20 }); // set display position
}

void Game::Compose(sf::RenderWindow & window) const
{
	for (int i = 0; i < int(grounds.size()); i++) {
		window.draw(grounds[i]);
	}
	for (int i = 0; i < int(bricks.size()); i++) {
		window.draw(bricks[i]);
	}
	for (int i = 0; i < int(enemies.size()); i++) {
		window.draw(enemies[i]);
	}
	for (int i = 0; i < int(healers.size()); i++) {
		window.draw(healers[i]);
	}

	window.draw(mario);
	window.draw(luigi);

	window.draw(score);
}
