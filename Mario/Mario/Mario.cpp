#include "Mario.h"

sf::Vector2i Mario::animationPlace(const unsigned & index)
{
	sf::Vector2i temp = {0,0};

	for (unsigned i = 0; i < index; i++) {
		temp.x += animation[i].x;
	}

	return temp;
}

void Mario::setPosition(const sf::Vector2f & position)
{
	sprite.setPosition(position);
}

void Mario::controls(const float &dt, const float &gravity) // * dt means pixels/second
{
	lastBounds = sprite.getGlobalBounds();
		
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { // left movement
		flipOrient = true;
		sprite.move(-600 * dt, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { // right movement
		flipOrient = false;
		sprite.move(600 * dt, 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !isJumping) { // enables jumping animation
		jumpVelocity = -1750;
		isJumping = true;
	}

	if (jumpVelocity < 0) { // animates jumping
		sprite.move({0, jumpVelocity * dt });
		jumpVelocity += gravity * dt;
	} else { // creates the feeling of gravity
		sprite.move({ 0, gForce * dt });
		gForce += gravity * dt;
	}
}

void Mario::collidesWith(const sf::FloatRect & object)
{
	if (sprite.getGlobalBounds().intersects(object)) {
		if (lastBounds.top + lastBounds.height <= object.top &&
			(lastBounds.left > object.left && lastBounds.left <= object.left + object.width ||
			 lastBounds.left + lastBounds.width >= object.left && 
			 lastBounds.left + lastBounds.width <= object.left + object.width)) // if mario comes from top
		{
			gForce = 0; // stop falling
			isJumping = false; // mario can't be jumping if touches the ground
			sprite.setPosition({sprite.getPosition().x, object.top - sprite.getGlobalBounds().height});
		}
		else {
			if (lastBounds.left + lastBounds.width <= object.left) { // colision with object's left
				sprite.setPosition({object.left - sprite.getGlobalBounds().width, sprite.getPosition().y});
			}else if (lastBounds.left >= object.left + object.width) { // colision with object's right
				sprite.setPosition({ object.left + object.width, sprite.getPosition().y });
			}
			else { // collision with objects bottom
				jumpVelocity = 0; // start falling
				sprite.setPosition({ sprite.getPosition().x, object.top + object.height });
			}
		}
	}
}

void Mario::animate(const float & dt)
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
	} else {
		animationTimer = 0;

		if(isJumping) animationFrame = 5; // jumping frame
		else animationFrame = 0; // idle frame
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		animationFrame = 4; // brake frame
	}

	// sprite.setTexture(Resources::mario_smallT);
	sprite.setTextureRect({ animationPlace(animationFrame).x,
							animationPlace(animationFrame).y,
							animation[animationFrame].x,
							animation[animationFrame].y });

	if (flipOrient) // flip orientation whenever you should
	{
		sprite.setTextureRect(
			{sprite.getTextureRect().left + sprite.getTextureRect().width, sprite.getTextureRect().top,
			 -sprite.getTextureRect().width, sprite.getTextureRect().height}
		);
	}
}

void Mario::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}
