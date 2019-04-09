#include "Enemy.h"

void Enemy::initializeIn(const sf::Vector2f & position)
{
	/*PHYSICS*/
	gForce = 0;

	/*AI*/
	srand(unsigned(time(NULL))); // reseeds random number
	direction = bool(rand() % 2); // starts in random direction
	dirTimer = 0;

	/*ANIMATION*/
	animationTimer = 0;
	isAlive = true;
	isVisible = true;

	/*POSITIONING*/
	sprite.setPosition(position);

	/*FRAME TYPE*/
	sprite.setTextureRect({ 0, 0, 16, 16 });
}

void Enemy::movement(const float & dt, const float & gravity)
{
	if (isAlive) {
		lastBounds = sprite.getGlobalBounds();
		int speed = rand() % 25 + 175; // adds a bit of random offset

		if (direction) { // left movement
			sprite.move(-speed * dt, 0);
		}
		else { // right movement
		   //flipOrient = false;
			sprite.move(speed * dt, 0);
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
}

void Enemy::brickCol(const sf::FloatRect & object)
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

void Enemy::animate(const float & dt)
{
	if (isAlive) {
		animationTimer += dt;

		if (animationTimer > animationLimit) {
			animationTimer = 0;

			sprite.setTextureRect(
				{ sprite.getTextureRect().left + sprite.getTextureRect().width, sprite.getTextureRect().top,
				 -sprite.getTextureRect().width, sprite.getTextureRect().height }
			);
		}
	}
	else {

		animationTimer += dt;

		if (animationTimer > deathLimit) {
			animationTimer = 0;

			isVisible = false;
		}

		sprite.setTextureRect(
			{ /*sprite.getTextureRect().left + */std::abs(sprite.getTextureRect().width), sprite.getTextureRect().top,
			std::abs(sprite.getTextureRect().width), sprite.getTextureRect().height }
		);
	}

}

void Enemy::charCol(Character& mario)
{
	if (sprite.getGlobalBounds().intersects(mario.getGlobalBounds()) && isAlive) {
		// if mario comes from top
		if (int(mario.getLastBounds().top + mario.getLastBounds().height) <= int(sprite.getGlobalBounds().top))
		{
			isAlive = false;
			animationTimer = 0; // makes sure animations will be nailed
		}
		else // in any other situation
		{
			mario.hurt();
		}
	}
}

void Enemy::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if(isVisible)
		target.draw(sprite);
}
