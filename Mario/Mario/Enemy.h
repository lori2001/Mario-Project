#pragma once
#include "SFML/Graphics.hpp"
#include "Resources.h"
#include "Character.h"
#include <math.h>

class Enemy : public sf::Drawable {
private:
	/*DISPLAY*/
		sf::Sprite sprite;

	/*PHYSICS*/
		sf::FloatRect lastBounds;
		float gForce; // gravity force applied at a given frame

	/*AI*/
		bool direction; // true is left false is right
		float dirTimer; // timer used to measure time passed while running smoothly
		const float dirLimit = 1.5f; // the frequency in seconds at which enemy changes direction

	/*MOVEMENT ANIMATION*/
		float animationTimer; // the timer used to measure time passed while running smoothly
		const float animationLimit = 0.2f; // the frequency in seconds at which movement animation works
	/*DEATH ANIMATION*/
		bool isAlive; // false whenever enemy should get squeezed and erased (disables most functions too)
		bool isVisible; // disables visibility whenever enemy does not exist
		const float deathLimit = 1.5f; // value in seconds after which the enemy will delete from the screen

public:
	Enemy() {
		sprite.setTexture(Resources::enemy_mushT);
		sprite.setScale({ 4.5f, 4.5f });
	}

	// sets up (and resets) default values of enemy and places it in position
	void initializeIn(const sf::Vector2f& position);
	
	// ! Should not be put into the events loop
	void movement(const float &dt, const float &gravity);
	// brick collision logic - Should always be after controls
	void brickCol(const sf::FloatRect &object);
	// Should always be after brick collision checks
	void animate(const float &dt);
	// check and act upon collision with character
	void charCol(Character& character);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};