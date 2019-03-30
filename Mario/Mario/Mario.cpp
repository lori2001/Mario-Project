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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && jumpToggle) { // enables jumping animation
		jumpVelocity = -1750;
		jumpToggle = false; // block jumping untile reallowed
		isJumping = true;
	}

	if (jumpVelocity < 0) { // animates jumping
		sprite.move({0, jumpVelocity * dt });
		jumpVelocity += gravity * dt;
	} else { // creates the feeling of gravity
		sprite.move({ 0, gForce * dt });
		gForce += gravity * dt;
		jumpToggle = false; // block jumping untile reallowed
	}
}

void Mario::collidesWith(const sf::FloatRect & object)
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
			isJumping = false; // mario can't be jumping if touches the ground
			jumpToggle = true; // allow jumping again
			sprite.setPosition({sprite.getPosition().x, object.top - sprite.getGlobalBounds().height});
		}
		// if mario comes from bottom
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

	if (!isJumping && sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
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
