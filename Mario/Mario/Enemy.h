#pragma once
#include "SFML/Graphics.hpp"
#include "Resources.h"
#include "Character.h"
#include "Score.h"
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
		bool isSqueezed; // death condition 1: true whenever enemy should be squeezed
		bool isFalling; // death condition 2: true whenever enemy should fall
		bool isVisible; // disables visibility whenever enemy does not exist
		const float deathLimit = 1.5f; // value in seconds after which the enemy will delete from the screen

public:
	Enemy(const sf::Vector2f& position) {
		sprite.setTexture(Resources::enemy_mushT);
		sprite.setScale({ 4.5f, 4.5f });

		initializeIn(position);
	}
	Enemy() : Enemy({ 0,0 }) {}

	// sets up (and resets) default values of enemy and places it in position
	void initializeIn(const sf::Vector2f& position);
	
	// ! Should not be put into the events loop
	void movement(const float dt, const float gravity);

	/*there is nothing in common between these, except for the name to ease map programming*/
	// ground collision logic
	void collision(Ground& object);
	// check and act upon collision with character
	void collision(Character& character);

	// animates movement of the enemy
	void animation(const float dt);


	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};