#include "Character.h"

sf::Vector2i Character::animationPlace(const unsigned & index)
{
	sf::Vector2i temp = {0,0};

	for (unsigned i = 0; i < index; i++) {
		temp.x += animation[i].x;
	}

	return temp;
}

void Character::controls(float dt, float gravity)
{
	// * dt (times dt) basically means means pixels/second

	if (isAlive) {
		lastBounds = sprite.getGlobalBounds();

		if (sf::Keyboard::isKeyPressed(left) && !sf::Keyboard::isKeyPressed(right)) { // left movement
			flipOrient = true;
			sprite.move(-600 * dt, 0);
		}
		if (sf::Keyboard::isKeyPressed(right) && !sf::Keyboard::isKeyPressed(left)) { // right movement
			flipOrient = false;
			sprite.move(600 * dt, 0);
		}

		if (sf::Keyboard::isKeyPressed(up) && jumpToggle) { // enables jumping animation
			jumpVelocity = -1550;
			jumpToggle = false; // block jumping untile reallowed
			isJumping = true;
		}

		/*acts upon character even if dead*/

		if (jumpVelocity < 0) { // animates jumping
			sprite.move({0, jumpVelocity * dt });
			jumpVelocity += gravity * dt;
		} else { // creates the feeling of gravity
			sprite.move({ 0, gForce * dt });
			gForce += gravity * dt;
			jumpToggle = false; // block jumping until reallowed
		}
	}
	else {
		sprite.move({ 0, jumpVelocity * dt });
		jumpVelocity += gravity * dt;
	}
}

void Character::changeCntrlKeys(const sf::Keyboard::Key & in_up, const sf::Keyboard::Key & in_down, const sf::Keyboard::Key & in_left, const sf::Keyboard::Key & in_right)
{
	up = in_up;
	down = in_down;
	left = in_left;
	right = in_right;
}

void Character::initializeIn(const sf::Vector2f & position)
{
	/*PHYSICS*/
	jumpToggle = false;
	isJumping = true;
	jumpVelocity = 0;
	gForce = 0;

	/*MOVEMENT ANIMATION*/
	flipOrient = false;
	animationTimer = 0;
	isAlive = true;
	lifeSignal = true;

	/*PROPERTIES*/
	lives = 2;
	isInvulnerable = false;
	invTimer = 0;
	invATimer = 0;
	isVisible = true;

	/*POSITIONING*/
	sprite.setPosition(position);
}

void Character::changeTexture(const sf::Texture & texture)
{
	sprite.setTexture(texture);
}

void Character::brickCol(const sf::FloatRect & object)
{
	if (sprite.getGlobalBounds().intersects(object) && isAlive) {
		// if character comes from top
		if (int(lastBounds.top + lastBounds.height) <= int(object.top) &&
		   ((int(lastBounds.left) > int(object.left) &&
			 int(lastBounds.left) < int(object.left + object.width)) ||
			(int(lastBounds.left) + int(sprite.getGlobalBounds().width) > int(object.left) &&
			 int(lastBounds.left) + int(sprite.getGlobalBounds().width) < int(object.left + object.width))))
		{
			gForce = 0; // stop falling
			isJumping = false; // character can't be jumping if touches the ground
			jumpToggle = true; // allow jumping again
			sprite.setPosition({sprite.getPosition().x, object.top - sprite.getGlobalBounds().height});
		}
		// if character comes from bottom
		else if (int(lastBounds.top) >= int(object.top + object.height) &&
			((int(lastBounds.left) > int(object.left) &&
			  int(lastBounds.left) < int(object.left + object.width)) ||
			 (int(lastBounds.left) + int(sprite.getGlobalBounds().width) > int(object.left) &&
			  int(lastBounds.left) + int(sprite.getGlobalBounds().width) < int(object.left + object.width))))
		{
			jumpVelocity = 0; // start falling
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

void Character::animate(const float & dt)
{
	if (isAlive)
	{
		if (!isJumping && lastBounds.left != sprite.getGlobalBounds().left) {
			animationTimer += dt;
			if (animationTimer > animationLimit) // if enough time has passed
			{
				animationTimer = 0;

				/*Rotate movement animation*/
				if (animationFrame == 0) animationFrame = 1;
				else if (animationFrame == 1) animationFrame = 2;
				else if (animationFrame == 2) animationFrame = 3;
				else if (animationFrame == 3) animationFrame = 1;
				else animationFrame = 0; // idle frame
			}
		}
		else {
			animationTimer = 0;

			if (isJumping) animationFrame = 5; // jumping frame
			else animationFrame = 0; // idle frame
		}

		if (!isJumping && sf::Keyboard::isKeyPressed(left) && sf::Keyboard::isKeyPressed(right)) {
			animationFrame = 4; // brake frame
		}

		sprite.setTextureRect({ animationPlace(animationFrame).x,
								animationPlace(animationFrame).y,
								animation[animationFrame].x,
								animation[animationFrame].y });

		if (flipOrient) // flip orientation whenever you should
		{
			sprite.setTextureRect(
				{ sprite.getTextureRect().left + sprite.getTextureRect().width, sprite.getTextureRect().top,
				 -sprite.getTextureRect().width, sprite.getTextureRect().height }
			);
		}

		if (isInvulnerable) // if the character is invulnerable
		{
			// filckering animation;
			invATimer += dt;
			invTimer += dt;

			if (invATimer > invALimit) { // animation
				invATimer = 0;
				isVisible = !isVisible;
			}

			if (invTimer > invALimit * 16) { // after 16 flickers
				invATimer = 0;
				invTimer = 0;
				isVisible = true;
				isInvulnerable = false;
			}
		}

		if (sprite.getPosition().y > HEIGHT) { // if character goes under screen
			isAlive = false; // trigger death animation
			gForce = 0; // reset gravity
			sprite.setPosition({sprite.getPosition().x , (float)HEIGHT}); // level out to make sure everything is ok
		}
	}
	else /*DEATH ANIMATION*/
	{
		// trick to do this only once without additional variables
		if (animationFrame != 6) {
			jumpVelocity = -1750;
		}

		animationFrame = 6;

		sprite.setTextureRect({ animationPlace(animationFrame).x,
		animationPlace(animationFrame).y,
		animation[animationFrame].x,
		animation[animationFrame].y });

		if (sprite.getPosition().y > HEIGHT + 100) { // +100 adds a small threshold
			lifeSignal = false; // signal death after all animations complete
		}
	}
}

void Character::hurt()
{
	if (!isInvulnerable)
	{
		lives--;

		if (lives <= 0) {
			isAlive = false;
			isInvulnerable = false;
		}
		else {
			isAlive = true;
			isInvulnerable = true;
		}
	}
}

void Character::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if(isVisible)
		target.draw(sprite, states);
}