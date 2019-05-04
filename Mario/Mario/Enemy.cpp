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
	isAlive = true;

	/*POSITIONING*/
	sprite.setPosition(position);

	/*FRAME TYPE*/
	sprite.setTextureRect({ 0, 0, 16, 16 });

	/*SOUND*/
	playSound = true;
}

void Enemy::movement(const float dt, const float gravity)
{
	if (!isSqueezed && isAlive) {
		if(!isFalling)
		{
			lastBounds = sprite.getGlobalBounds();
			int speed = rand() % 25 + 175; // adds a bit of random offset

			if (direction) { // left movement
				sprite.move(-speed * dt, 0);
			}
			else { // right movement
				sprite.move(speed * dt, 0);
			}

			dirTimer += dt;

			if (dirTimer > dirLimit) {
				dirTimer = 0;

				if (direction) direction = false;
				else direction = true;
			}
		}
		else { // if is no falling
			if (playSound && kickSound.getStatus() != sf::Music::Status::Playing) {
				kickSound.play();
				playSound = false;
			}
		}

		sprite.move({ 0, gForce * dt });
		gForce += gravity * dt;
	}

	// if enemy falls under this threshold, there is no sense to calculate movements and do logic
	if (sprite.getPosition().y > HEIGHT + 100) {
		isAlive = false;
	}
}

void Enemy::collision(Ground & object)
{
	if (isAlive) {
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
					Score::changeScore(75); // gives points
				}
			}
		}
	}
}

void Enemy::animation(const float dt)
{
	if (isAlive) {
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
		else if (isSqueezed) {
			if (playSound && stompSound.getStatus() != sf::Music::Status::Playing) {
				stompSound.play();
				playSound = false;
			}

			animationTimer += dt;

			if (animationTimer > deathLimit) {
				animationTimer = 0;

				isAlive = false;
			}

			sprite.setTextureRect(
				{ /*sprite.getTextureRect().left + */std::abs(sprite.getTextureRect().width), sprite.getTextureRect().top,
				std::abs(sprite.getTextureRect().width), sprite.getTextureRect().height }
			);
		}
	}
}

void Enemy::collision(Character& character)
{
	if (sprite.getGlobalBounds().intersects(character.getGlobalBounds()) && !isSqueezed && !isFalling && isAlive) {
		// if mario comes from top
		if (int(character.getLastBounds().top + character.getLastBounds().height) <= int(sprite.getGlobalBounds().top))
		{
			animationTimer = 0; // makes sure animations will be nailed
			isSqueezed = true; // squeezes enemy
			Score::changeScore(100); // gives score points
			character.jump(800); // makes character jump
		}
		else // in any other situation
		{
			character.hurt(); // hurts character
		}
	}
}

void Enemy::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if(isAlive)
		target.draw(sprite);
}
