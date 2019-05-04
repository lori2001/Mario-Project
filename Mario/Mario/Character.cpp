#include "Character.h"

sf::Vector2i Character::animationPlace(const unsigned & index)
{
	sf::Vector2i temp = {0,0};

	for (unsigned i = 0; i < index; i++) {
		temp.x += animationSizes[i].x;
	}

	return temp;
}

void Character::movement(float dt, float gravity, sf::View& view)
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
			// play sound
			jumpSound.play();
			
			jumpVelocity = -260 * sprite.getScale().x; // the force with which jumping occurs
			jumpToggle = false; // block jumping until reallowed
			isJumping = true; // signal that character is jumping
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

		// if character is almost at the end of the screen and view does not exceed the length of map
		if (sprite.getPosition().x > view.getCenter().x + view.getSize().x / 8 &&
			view.getCenter().x + view.getSize().x / 2 < Maps::getMapLength()) {
			view.move(650 * dt,0); // move camera away a little faster than the character can move
		}
		else if (sprite.getPosition().x <= view.getCenter().x - view.getSize().x / 2) { // else if the character is off screen in the leftmost part
			sprite.setPosition(view.getCenter().x - view.getSize().x / 2 + 1, sprite.getPosition().y); // block character from going off
		}
		else if (sprite.getPosition().x + sprite.getGlobalBounds().width > Maps::getMapLength()) { // else if the character goes off screen in the rightmost part
			sprite.setPosition(view.getCenter().x + view.getSize().x / 2 - sprite.getGlobalBounds().width, sprite.getPosition().y); // block character from going off
		}

		// update hears position each frame based on current view
		for (int i = 0; i < int(hearts.size()); i++) {
			hearts[i].setPosition(view.getCenter().x - view.getSize().x / 2 + heartspos.x, view.getCenter().y - view.getSize().y / 2 + heartspos.y);
			hearts[i].move({ float(heartoffset.x * i) , heartoffset.y });
		}
	}
	else {
		sprite.move({ 0, jumpVelocity * dt });
		jumpVelocity += gravity * dt;
	}
}

void Character::setCntrlKeys(const sf::Keyboard::Key & in_up, const sf::Keyboard::Key & in_down, const sf::Keyboard::Key & in_left, const sf::Keyboard::Key & in_right)
{
	up = in_up;
	down = in_down;
	left = in_left;
	right = in_right;
}

void Character::changeHeartsPos(const sf::Vector2f & position)
{
	heartspos = position;
}

void Character::jump(const unsigned velocity)
{
	// converts value to negative because in SFML that means up
	jumpVelocity = -float(velocity);
	// make sure gravity doesn't mess up things
	gForce = 0;
}

void Character::doNotDisplay()
{
	lives = 0;
	isAlive = false;
	isVisible = false;
	lifeSignal = false;
}

void Character::initializeIn(const sf::Vector2f & position, const float scale)
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
	sprite.setScale({ scale,scale });

	hearts.clear();
	for (int i = 0; i < lives; i++) {
		hearts.push_back(sf::Sprite{ Resources::heartT });
		hearts[i].setPosition(heartspos);
		hearts[i].move({ float(heartoffset.x * i) , heartoffset.y });
		hearts[i].setScale({1.8f, 1.8f});
	}
}

void Character::changeTexture(const sf::Texture & texture)
{
	sprite.setTexture(texture);
}

void Character::collision(Ground & object)
{
	for (int i = 0; i < object.getRowSize(); i++)
	{
		if (sprite.getGlobalBounds().intersects(object.getGlobalBounds(i)) && isAlive) {
			// LASTBOUND COLLISION
			// if character comes from top
			if (int(lastBounds.top + lastBounds.height) <= int(object.getGlobalBounds(i).top))
			{
				gForce = 0; // stop falling
				isJumping = false; // character can't be jumping if touches the ground
				jumpToggle = true; // allow jumping again

				sprite.setPosition({ sprite.getPosition().x, object.getGlobalBounds(i).top - sprite.getGlobalBounds().height });
			}
			// if character comes from bottom
			else if (int(lastBounds.top) >= int(object.getGlobalBounds(i).top + object.getGlobalBounds(i).height))
			{
				object.moveIfShould(i); // animates not solid objects (canMove = true)
				jumpVelocity = 0; // start falling
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
			// HALFPOINT COLLISION
			// if character comes from bottom
			else if (sprite.getGlobalBounds().top > object.getGlobalBounds(i).top + object.getGlobalBounds(i).height / 2) {
				jumpVelocity = 0; // start falling
				sprite.setPosition({ sprite.getPosition().x, object.getGlobalBounds(i).top + object.getGlobalBounds(i).height });
			}
			else {
				gForce = 0; // stop falling
				sprite.setPosition({ sprite.getPosition().x, object.getGlobalBounds(i).top - sprite.getGlobalBounds().height });
			}
		}
	}
}

void Character::animation(const float dt)
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
								animationSizes[animationFrame].x,
								animationSizes[animationFrame].y });

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
			lives = 0;
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
		animationSizes[animationFrame].x,
		animationSizes[animationFrame].y });

		if (sprite.getPosition().y > HEIGHT + 100) { // +100 adds a small threshold
			lifeSignal = false; // signal death after all animations complete
		}
	}
}

bool Character::hurt()
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

		return true;
	}

	return false;
}

bool Character::heal()
{
	if (isAlive)
	{
		lives++;

		if (lives > int(hearts.size())) {
			hearts.push_back(hearts[hearts.size() - 1]); // add one more hearth to vector
			// remember size auto increments
			hearts[hearts.size() - 1].move(heartoffset); // move it a bit to not be drawn in the same place
		}

		return true;
	} else 

	return false;
}

void Character::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if(isVisible)
		target.draw(sprite, states);

	for (int i = 0; i < lives; i++) {
		target.draw(hearts[i], states);
	}
}
