#include "UserInterface.h"

void UserInterface::Setup(sf::RenderWindow & window)
{
	open.setTexture(Resources::open_iconT);
	open.setScale({ 0.13f, 0.13f });
	open.setPosition({ 10, 10 });

	save.setTexture(Resources::save_iconT);
	save.setScale({ 0.1f,0.1f });
	save.setPosition({ 85, 10 });
	background.setFillColor(sf::Color(70,140,226));

	// TODO: Keep the same scale as in-game
	ground.setTexture(Resources::groundT);
	ground.setScale({ 1.4f,1.4f });
	ground.setPosition({ 800, 10 });

	brick.setTexture(Resources::brickT);
	brick.setScale({ 1.4f,1.4f });
	brick.setPosition({ 900, 10 });

	enemy.setTexture(Resources::enemy_mushT);
	enemy.setScale({ 3.5f,3.5f });
	enemy.setPosition({ 1000, 10 });

	healer.setTexture(Resources::good_mushT);
	healer.setScale({ 3.5f,3.5f });
	healer.setPosition({ 1100, 10 });

	mario.setTexture(Resources::mario_smallT);
	mario.setScale({ 3.7f,3.7f });
	mario.setPosition({ 1200, 10 });

	luigi.setTexture(Resources::luigi_smallT);
	luigi.setScale({ 3.7f,3.7f });
	luigi.setPosition({ 1300, 10 });
}

void UserInterface::handleEvents(const sf::RenderWindow & window, const sf::Event & event)
{
	mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window)); //gets mouse position relative to window

	open.selectByMouse(mouse);
	open.handleEvents(event);

	save.selectByMouse(mouse);
	save.handleEvents(event);

	ground.selectByMouse(mouse);
	ground.handleEvents(event);

	brick.selectByMouse(mouse);
	brick.handleEvents(event);

	enemy.selectByMouse(mouse);
	enemy.handleEvents(event);

	healer.selectByMouse(mouse);
	healer.handleEvents(event);

	mario.selectByMouse(mouse);
	mario.handleEvents(event);

	luigi.selectByMouse(mouse);
	luigi.handleEvents(event);
}

void UserInterface::Update(sf::RenderWindow & window)
{
	if (open.activated()) {

	}
	else if (save.activated()) {

	}
	else if (ground.activated()) {
		Mouse::setSelected(Mouse::groundID);
	}
	else if (brick.activated()) {
		Mouse::setSelected(Mouse::brickID);
	}
	else if (enemy.activated()) {
		Mouse::setSelected(Mouse::enemyID);
	}
	else if (healer.activated()) {
		Mouse::setSelected(Mouse::healerID);
	}
	else if (mario.activated()) {
		Mouse::setSelected(Mouse::marioID);
	}
	else if (luigi.activated()) {
		Mouse::setSelected(Mouse::luigiID);
	}
}

void UserInterface::Compose(sf::RenderWindow & window)
{
	window.draw(background);
	window.draw(open);
	window.draw(save);
	window.draw(ground);
	window.draw(brick);
	window.draw(enemy);
	window.draw(healer);
	window.draw(mario);
	window.draw(luigi);
}
