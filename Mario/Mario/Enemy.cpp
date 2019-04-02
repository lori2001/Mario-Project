#include "Enemy.h"

void Enemy::setPosition(const sf::Vector2f & position)
{
	sprite.setPosition(position);
}

void Enemy::controls(const float & dt, const float & gravity)
{
	lastBounds = sprite.getGlobalBounds();

	if (direction) { // left movement
		//flipOrient = true;
		sprite.move(-200 * dt, 0);
	}else { // right movement
		//flipOrient = false;
		sprite.move(200 * dt, 0);
	}

	dirTimer += dt;

	if (dirTimer > dirLimit) {
		dirTimer = 0;

		if (direction) direction = false;
		else direction = true;
	}

	sprite.move({ 0, gForce * dt });
	gForce += gravity * dt;
}

void Enemy::collidesWith(const sf::FloatRect & object)
{
	if (sprite.getGlobalBounds().intersects(object)) {
		// if mario comes from top
		if (int(lastBounds.top + lastBounds.height) <= int(object.top) &&
			((int(lastBounds.left) > int(object.left) &&
				int(lastBounds.left) < int(object.left + object.width)) ||
				(int(lastBounds.left) + int(sprite.getGlobalBounds().width) > int(object.left) &&
					int(lastBounds.left) + int(sprite.getGlobalBounds().width) < int(object.left + object.width))))
		{
			gForce = 0; // stop falling
			sprite.setPosition({ sprite.getPosition().x, object.top - sprite.getGlobalBounds().height });
		}
		// if mario comes from bottom
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

void Enemy::kill(const sf::FloatRect & object, sf::RenderWindow& tmp)
{
	if (sprite.getGlobalBounds().intersects(object)) {
		tmp.close();
	}
}

void Enemy::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite);
}
