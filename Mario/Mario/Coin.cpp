#include "Coin.h"

sf::Vector2i Coin::animationPlace(const unsigned & index)
{
	sf::Vector2i temp = { 0,0 };

	for (unsigned i = 0; i < index; i++) {
		temp.x += int(size.x);
	}

	return temp;
}

void Coin::initializeIn(const sf::Vector2f & position)
{
	/*PROPERTIES*/
	isAlive = true;

	/*POSITIONING*/
	sprite.setPosition(position);

	/*FRAME TYPE*/
	currFrame = 0;
	sprite.setTextureRect({ 0, 0, int(size.x), int(size.y) });

	/*ANIMATION*/
	animationTimer = 0;
	animationLimit = 0.25f;
}

void Coin::animation(const float dt)
{
	animationTimer += dt;

	/*Front frame displays for more time*/
	if (currFrame == 0) {
		animationLimit = 0.25f;
	}
	else {
		animationLimit = 0.15f;
	}

	if (animationTimer > animationLimit) {
		animationTimer = 0;

		currFrame++;
		if (currFrame > 3) {
			currFrame = 0;
		}

		sprite.setTextureRect({ animationPlace(currFrame).x, 0, int(size.x), int(size.y) });
	}
}

void Coin::collision(const Character& character)
{
	if (isAlive && sprite.getGlobalBounds().intersects(character.getGlobalBounds()) && character.getlifeSignal()) {
		sound.play();

		isAlive = false;
		Score::add(50);
	}
}

void Coin::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (isAlive)
		target.draw(sprite);
}
