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

void Mario::controls(const float &dt, const float &gravity) // * dt means pixels/second
{
	lastBounds = sprite.getGlobalBounds();
		
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { // left movement
		flipOrient = true;
		sprite.move(-600 * dt, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { // right movement
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
			gForce = 0;
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
{ // TODO: Fix textures to avoid chicken head
	if (!isJumping && lastBounds.left != sprite.getGlobalBounds().left) {
			animationTimer += dt;
			if (animationTimer > animationLimit) { // if enough time has passed
				animationTimer = 0;
				walkingAnim = !walkingAnim;
			}
	} else {
		walkingAnim = isJumping;
		animationTimer = 0;
	}

	if(walkingAnim){
		sprite.setTexture(Resources::mario_walkT);
		sprite.setTextureRect({ 0 , 0, (int)Resources::mario_walkT.getSize().x, (int)Resources::mario_walkT.getSize().y });
	}
	else {
		sprite.setTexture(Resources::mario_standT);
		sprite.setTextureRect({ 0 , 0, (int)Resources::mario_standT.getSize().x, (int)Resources::mario_standT.getSize().y });
	}

	if(flipOrient) // flip orientation whenever you should
	{
		sprite.setTextureRect(
			sf::IntRect(sprite.getTextureRect().width, 0,
				-sprite.getTextureRect().width, sprite.getTextureRect().height)
		);
	}
}

void Mario::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}
