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
	isSqueezed = false;
	isFalling = false;
	isVisible = true;

	/*POSITIONING*/
	sprite.setPosition(position);

	/*FRAME TYPE*/
	sprite.setTextureRect({ 0, 0, 16, 16 });
}

void Enemy::movement(const float dt, const float gravity)
{
	if (!isSqueezed) {
		if(!isFalling)
		{
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
		}
		sprite.move({ 0, gForce * dt });
		gForce += gravity * dt;
	}

	// if enemy falls under this threshold, there is no sense to calculate movements and do logic
	if (sprite.getPosition().y > HEIGHT + 100) {
		isSqueezed = true;
		isFalling = true;
	}
}

void Enemy::collision(Ground & object)
{
	for (int i = 0; i < object.getRowSize(); i++)
	{
		if (sprite.getGlobalBounds().intersects(object.getGlobalBounds(i)) && !isFalling) {
			// if character comes from top
			if (int(lastBounds.top + lastBounds.height) <= int(object.getGlobalBounds(i).top))
			{
				gForce = 0; // stop falling
				sprite.setPosition({ sprite.getPosition().x, object.getGlobalBounds(i).top - sprite.getGlobalBounds().height });
			}
			// if character comes from bottom
			else if (int(lastBounds.top) >= int(object.getGlobalBounds(i).top + object.getGlobalBounds(i).height))
			{
				sprite.setPosition({ sprite.getPosition().x, object.getGlobalBounds(i).top + object.getGlobalBounds(i).height });
			}
			// if character comes from left
			else if (int(lastBounds.left + lastBounds.width) <= int(object.getGlobalBounds(i).left)) {
				sprite.setPosition({ object.getGlobalBounds(i).left - sprite.getGlobalBounds().width, sprite.getPosition().y });
			}
			// if character comes from right
			else if (int(lastBounds.left) >= int(object.getGlobalBounds(i).left + object.getGlobalBounds(i).width)) {
				sprite.setPosition({ object.getGlobalBounds(i).left + object.getGlobalBounds(i).width, sprite.getPosition().y });
			}
			else {
				// gets triggered whenever the ground moves below the entity and not vice-versa
				isFalling = true;
			}
		}
	}
}

void Enemy::animation(const float dt)
{
	if (!isSqueezed && !isFalling) {
		animationTimer += dt;

		if (animationTimer > animationLimit) {
			animationTimer = 0;

			sprite.setTextureRect(
				{ sprite.getTextureRect().left + sprite.getTextureRect().width, sprite.getTextureRect().top,
				 -sprite.getTextureRect().width, sprite.getTextureRect().height }
			);
		}
	}
	else if(isSqueezed) {

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

void Enemy::collision(Character& character)
{
	if (sprite.getGlobalBounds().intersects(character.getGlobalBounds()) && !isSqueezed && !isFalling) {
		// if mario comes from top
		if (int(character.getLastBounds().top + character.getLastBounds().height) <= int(sprite.getGlobalBounds().top))
		{
			isSqueezed = true;
			animationTimer = 0; // makes sure animations will be nailed
			character.jump(800);
		}
		else // in any other situation
		{
			character.hurt();
		}
	}
}

void Enemy::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if(isVisible)
		target.draw(sprite);
}
