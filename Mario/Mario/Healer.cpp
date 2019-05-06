#include "Healer.h"

void Healer::initializeIn(const sf::Vector2f & position)
{
	/*PHYSICS*/
	gForce = 0;

	/*PROPERTIES*/
	isAlive = true;

	/*POSITIONING*/
	sprite.setPosition(position);
}

void Healer::movement(const float & dt, const float & gravity)
{
	if (isAlive) {
		lastBounds = sprite.getGlobalBounds();

		sprite.move(350 * dt, 0); // always moves right

		sprite.move({ 0, gForce * dt });
		gForce += gravity * dt;
	}
}

void Healer::collision(Ground & object)
{
	for (int i = 0; i < object.getRowSize(); i++)
	{
		if (sprite.getGlobalBounds().intersects(object.getGlobalBounds(i)) && isAlive) {
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
				gForce = 0; // stop falling
				sprite.setPosition({ sprite.getPosition().x, object.getGlobalBounds(i).top - sprite.getGlobalBounds().height });
			}
		}
	}
}

void Healer::collision(Character& character)
{
	if (isAlive && sprite.getGlobalBounds().intersects(character.getGlobalBounds())) {
		if (character.heal()) { // small bugfix
			isAlive = false;
		}
	}
}

void Healer::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (isAlive)
		target.draw(sprite);
}
