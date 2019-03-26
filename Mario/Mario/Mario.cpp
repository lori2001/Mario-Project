#include "Mario.h"

void Mario::setPosition(const sf::Vector2f & position)
{
	sprite.setPosition(position);
}

void Mario::setScale(const sf::Vector2f & scale)
{
	sprite.setScale(scale);
}

void Mario::controls(const float &dt, const float &gravity) // * dt means pixels/second
{
	lastBounds = sprite.getGlobalBounds();
		
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { sprite.move(-600 * dt, 0); } // left movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { sprite.move(600 * dt, 0); } // rgiht movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !inAir) { // enables jumping animation
		jumpVelocity = -1750;
	}

	if (jumpVelocity < 0) { // animates jumping
		sprite.move({0, jumpVelocity * dt });
		jumpVelocity += gravity * dt;
	} else { // creates the feeling of gravity
		sprite.move({ 0, gForce * dt });
		gForce += gravity * dt;
	}

	inAir = true; // suppose that it is in the air
}

void Mario::collidesWith(const sf::FloatRect & object)
{
	if (sprite.getGlobalBounds().intersects(object)) {
		if (lastBounds.top + lastBounds.height <= object.top &&
			(lastBounds.left > object.left && lastBounds.left <= object.left + object.width ||
			 lastBounds.left + lastBounds.width >= object.left && 
			 lastBounds.left + lastBounds.width <= object.left + object.width)) // if mario comes from top
		{
			gForce = 0;
			inAir = false; // negate that it is in the air
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

void Mario::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}
