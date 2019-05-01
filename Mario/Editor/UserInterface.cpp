#include "UserInterface.h"

void UserInterface::Setup()
{
	background.setFillColor(sf::Color(70, 140, 226));

	open.setTexture(Resources::open_iconT);
	open.setScale({ 0.13f, 0.13f });

	save.setTexture(Resources::save_iconT);
	save.setScale({ 0.1f,0.1f });

	ground.setTexture(Resources::groundT);
	ground.setScale({ 1.4f,1.4f });

	brick.setTexture(Resources::brickT);
	brick.setScale({ 1.4f,1.4f });

	enemy.setTexture(Resources::enemy_mushT);
	enemy.setScale({ 3.5f,3.5f });

	healer.setTexture(Resources::good_mushT);
	healer.setScale({ 3.5f,3.5f });

	mario.setTexture(Resources::mario_smallT);
	mario.setScale({ 3.7f,3.7f });

	luigi.setTexture(Resources::luigi_smallT);
	luigi.setScale({ 3.7f,3.7f });	

	coin.setTexture(Resources::coinT);
	coin.setScale({ 4.0f,3.7f });

	endpoint.setTexture(Resources::castle_smallT);
	endpoint.setScale({ 0.3f,0.3f });

	eraser.setFillColor(sf::Color::Red);
	updatePos({ 0,0 });
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

	coin.selectByMouse(mouse);
	coin.handleEvents(event);

	endpoint.selectByMouse(mouse);
	endpoint.handleEvents(event);

	eraser.selectByMouse(mouse);
	eraser.handleEvents(event);
}

void UserInterface::Update(sf::View& view)
{
	updatePos({ view.getCenter().x - view.getSize().x / 2, view.getCenter().y - view.getSize().y / 2 });

	if (open.activated() && Paths::openFilePath()) {
		opening = true;
	}
	else if (save.activated() && Paths::saveFilePath()) {
		saveing = true;
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
	else if (coin.activated()) {
		Mouse::setSelected(Mouse::coinID);
	}
	else if (endpoint.activated()) {
		Mouse::setSelected(Mouse::endpointID);
	}
	else if (eraser.activated()) {
		Mouse::setSelected(Mouse::eraserID);
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
	window.draw(coin);
	window.draw(endpoint);
	window.draw(eraser);
}

void UserInterface::updatePos(const sf::Vector2f & relativePos)
{
	background.setPosition(relativePos);
	open.setPosition({ relativePos.x + 10, relativePos.y + 10 });
	save.setPosition({ relativePos.x + 85, relativePos.y + 10 });
	ground.setPosition({ relativePos.x + 800, relativePos.y + 10 });
	brick.setPosition({ relativePos.x + 900, relativePos.y + 10 });
	enemy.setPosition({ relativePos.x + 1000, relativePos.y + 10 });
	healer.setPosition({ relativePos.x + 1100, relativePos.y + 10 });
	mario.setPosition({ relativePos.x + 1200, relativePos.y + 10 });
	luigi.setPosition({ relativePos.x + 1300, relativePos.y + 10 });
	coin.setPosition({ relativePos.x + 1400, relativePos.y + 10 });
	endpoint.setPosition({ relativePos.x + 1500, relativePos.y + 10 });
	eraser.setPosition({ relativePos.x + 1600, relativePos.y + 10 });
}