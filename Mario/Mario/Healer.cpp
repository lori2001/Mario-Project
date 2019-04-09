#include "Healer.h"

void Healer::initializeIn(const sf::Vector2f & position)
{
	/*PHYSICS*/
	gForce = 0;

	/*ANIMATION*/
	isAlive = true;

	/*POSITIONING*/
	sprite.setPosition(position);

	/*FRAME TYPE*/
	sprite.setTextureRect({ 0, 0, 16, 16 });
}

void Healer::movement(const float & dt, const float & gravity)
{
	if (isAlive) {
		lastBounds = sprite.getGlobalBounds();

		sprite.move(350 * dt, 0); // always moves right

		sprite.move({ 0, gForce * dt });
		gForce += gravity * dt;
	}
}

void Healer::brickCol(const sf::FloatRect & object)
{
	if (sprite.getGlobalBounds().intersects(object) && isAlive) {
		// if sprite comes from top
		if (int(lastBounds.top + lastBounds.height) <= int(object.top) &&
			((int(lastBounds.left) > int(object.left) &&
				int(lastBounds.left) < int(object.left + object.width)) ||
				(int(lastBounds.left) + int(sprite.getGlobalBounds().width) > int(object.left) &&
					int(lastBounds.left) + int(sprite.getGlobalBounds().width) < int(object.left + object.width))))
		{
			gForce = 0; // stop falling
			sprite.setPosition({ sprite.getPosition().x, object.top - sprite.getGlobalBounds().height });
		}
		// if sprite comes from bottom
		else if (int(lastBounds.top) >= int(object.top + object.height) &&
			((int(lastBounds.left) > int(object.left) &&
				int(lastBounds.left) < int(object.left + object.width)) ||
				(int(lastBounds.left) + int(sprite.getGlobalBounds().width) > int(object.left) &&
					int(lastBounds.left) + int(sprite.getGlobalBounds().width) < int(object.left + object.width))))
		{
			sprite.setPosition({ sprite.getPosition().x, object.top + object.height });
		}
		else if (int(lastBounds.left + lastBounds.width) <= int(object.left)) { // colision with object's left
			sprite.setPosition({ object.left - sprite.getGlobalBounds().width, sprite.getPosition().y });
		}
		else if (int(lastBounds.left) >= int(object.left + object.width)) { // colision with object's right
			sprite.setPosition({ object.left + object.width, sprite.getPosition().y });
		}
		else { // this should never activate but I would like to get warned if it does
			std::cout << "WARNING: Undiscussed collision situation!" << std::endl;
		}
	}
}

void Healer::charCol(Character& character)
{
	if (isAlive && sprite.getGlobalBounds().intersects(character.getGlobalBounds())) {
		isAlive = false;
		character.heal();
	}
}

void Healer::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (isAlive)
		target.draw(sprite);
}
