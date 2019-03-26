#include "Mario.h"
#include <iostream>

void Mario::setPosition(const sf::Vector2f & position)
{
	sprite.setPosition(position);
}

void Mario::setScale(const sf::Vector2f & scale)
{
	sprite.setScale(scale);
}

void Mario::setTexture(const sf::Texture & texture)
{
	sprite.setTexture(texture);
}

void Mario::controls(const float &dt, const float &gravity) // * dt means pixels/second
{
	lastBounds = sprite.getGlobalBounds();
		
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { sprite.move(-600 * dt, 0); }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { sprite.move(600 * dt, 0); }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !inAir) {
		jumpVelocity = -1750;
	}

	if (jumpVelocity < 0) {
		sprite.move({0, jumpVelocity * dt });
		jumpVelocity += gravity * dt;
	} else {
		sprite.move({ 0, gForce * dt });
		gForce += gravity * dt;
	}

	inAir = true;
}

void Mario::collidesWith(const sf::FloatRect & object)
{
	if (sprite.getGlobalBounds().intersects(object)) {
		if (lastBounds.top + lastBounds.height < object.top &&
			(lastBounds.left > object.left && lastBounds.left < object.left + object.width ||
			 lastBounds.left + lastBounds.width > object.left && 
			 lastBounds.left + lastBounds.width < object.left + object.width)) 
		{
			gForce = 0;
			inAir = false;
			sprite.setPosition({sprite.getPosition().x, object.top - (2 + sprite.getGlobalBounds().height)});
		}
	}
}

void Mario::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}
