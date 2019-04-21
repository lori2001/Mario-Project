#pragma once
#include "SFML/Graphics.hpp"
#include "Resources.h"
#include "Character.h"
#include "Score.h"
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
	Healer(const sf::Vector2f& position, const float scale = 4) {
		sprite.setTexture(Resources::good_mushT);
		sprite.setScale({ scale, scale });
	
		initializeIn(position);
	}
	Healer() : Healer({0,0}) {}

	// sets up (and resets) default values of enemy and places it in position
	void initializeIn(const sf::Vector2f& position);

	// ! Should not be put into the events loop
	void movement(const float &dt, const float &gravity);

	/*there is nothing in common between these, except for the name to ease map programming*/
	// ground collision logic
	void collision(Ground& object);
	// check and act upon collision with character
	void collision(Character& character);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};