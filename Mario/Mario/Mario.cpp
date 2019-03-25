#include "Mario.h"

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

void Mario::controls(const float &dt, const float &gravity)
{
	// * dt means pixels/second

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { sprite.move(-300 * dt, 0); }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { sprite.move(300 * dt, 0); }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		jumpVelocity = 1000;
	}

	if (jumpVelocity >= 0) {
		sprite.move({0, -(jumpVelocity * dt)});
		jumpVelocity -= gravity;
	}
	else {
		sprite.move({ 0, +(jumpVelocity * dt) });
		jumpVelocity += gravity;
	}
}

void Mario::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}
