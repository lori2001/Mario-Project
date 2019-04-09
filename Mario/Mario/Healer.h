#pragma once
#include "SFML/Graphics.hpp"
#include "Resources.h"
#include "Character.h"
#include <math.h>

class Healer : public sf::Drawable {
private:
	/*DISPLAY*/
	sf::Sprite sprite;

	/*PHYSICS*/
	sf::FloatRect lastBounds;
	float gForce; // gravity force applied at a given frame

	/*PROPERTIES*/
		bool isAlive; // false whenever enemy should get squeezed and erased (disables most functions too)

public:
	Healer() {
		sprite.setTexture(Resources::good_mushT);
		sprite.setScale({ 4, 4 });
	}

	// sets up (and resets) default values of enemy and places it in position
	void initializeIn(const sf::Vector2f& position);

	// ! Should not be put into the events loop
	void movement(const float &dt, const float &gravity);
	// brick collision logic - Should always be after controls
	void brickCol (const sf::FloatRect &object);
	// check and act upon collision with character
	void charCol(Character& character);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};