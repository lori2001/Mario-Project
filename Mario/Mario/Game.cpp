#include "Game.h"

void Game::Setup(sf::RenderWindow & window)
{
	score.equal(0); // reset score if needed
	
	/* Load in game info into actual game elements*/
	mario.initializeIn(Maps::getCharacter1().pos, Maps::getCharacter1().scale);
	mario.setCntrlKeys(sf::Keyboard::Up,
		sf::Keyboard::Down,
		sf::Keyboard::Left,
		sf::Keyboard::Right);

	if (Maps::getCharacter1().pos.x == notfound && Maps::getCharacter1().pos.y == notfound) {
		mario.doNotDisplay();
	}

	luigi.initializeIn(Maps::getCharacter2().pos, Maps::getCharacter2().scale);
	luigi.setCntrlKeys(sf::Keyboard::W,
		sf::Keyboard::S,
		sf::Keyboard::A,
		sf::Keyboard::D);
	luigi.changeTexture(Resources::luigi_smallT);
	luigi.changeHeartsPos({ 20,60 });

	if (Maps::getCharacter2().pos.x == notfound && Maps::getCharacter2().pos.y == notfound) {
		luigi.doNotDisplay();
	}

	if (Maps::getEndpoint().pos.x != notfound && Maps::getEndpoint().pos.y != notfound) {
		endpoint.initializeIn(Maps::getEndpoint().pos, Maps::getEndpoint().scale);
	}

	enemies.clear();
	for (int i = 0; i < Maps::getEnemiesNum(); i++) {
		enemies.push_back(Enemy{ Maps::getEnemy(i).pos, Maps::getEnemy(i).scale });
	}
	healers.clear();
	for (int i = 0; i < Maps::getHealersNum(); i++) {
		healers.push_back(Healer{ Maps::getHealer(i).pos, Maps::getHealer(i).scale });
	}
	coins.clear();
	for (int i = 0; i < Maps::getCoinsNum(); i++) {
		coins.push_back(Coin{ Maps::getCoin(i).pos, Maps::getCoin(i).scale });
	}
	bricks.clear();
	for (int i = 0; i < Maps::getBricksNum(); i++) {
		bricks.push_back(Brick{ Maps::getBrick(i).pos, Maps::getBrick(i).scale, Maps::getBrick(i).size });
	}
	grounds.clear();
	for (int i = 0; i < Maps::getGroundsNum(); i++) {
		grounds.push_back(Ground{ Maps::getGround(i).pos, Maps::getGround(i).scale, Maps::getGround(i).size });
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
	endpoint.detection(mario,elapsedTime);
	mario.animation(elapsedTime);

	luigi.movement(elapsedTime, gravity, view);
	endpoint.detection(luigi, elapsedTime);
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

	for (int i = 0; i < int(coins.size()); i++) {
		coins[i].animation(elapsedTime);
		coins[i].collision(mario);
		coins[i].collision(luigi);
	}

	// check if mario and luigi are still alive and deactivate game if they are not
	if (!mario.getlifeSignal() && !luigi.getlifeSignal()) {
		isWon = false;
		isActive = false;
	}
	else if (endpoint.getGameWon()) {
		isWon = true;
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
	for (int i = 0; i < int(coins.size()); i++) {
		window.draw(coins[i]);
	}

	window.draw(endpoint);
	window.draw(mario);
	window.draw(luigi);

	window.draw(score);
}
