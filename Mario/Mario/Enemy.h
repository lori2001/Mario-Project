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
	float gForce = 0; // gravity force applied at a given frame

	/*AI*/
	bool direction = false; // true is left false is right
	float dirTimer = 0; // timer used to measure time passed while running smoothly
	float dirLimit = 1.5f; // the frequency in seconds at which enemy changes direction

	/*ANIMATION*/
	float animationTimer = 0; // the timer used to measure time passed while running smoothly
	float animationLimit = 0.2f; // the frequency in seconds at which movement animation works
		/*death animation*/
		bool isAlive = true;
		float deathLimit = 1.5f; // value in seconds after which the enemy will delete from the screen

public:
	Enemy() {
		sprite.setTexture(Resources::enemy_mushT);
		sprite.setScale({ 4.5f, 4.5f });
		sprite.setTextureRect({0, 0, 16, 16});
	}
	void setPosition(const sf::Vector2f& position);

	// ! Should not be put into the events loop
	void movement(const float &dt, const float &gravity);
	// Should always be after controls
	void collidesWith(const sf::FloatRect &object);
	// Should always be after collision checks
	void animate(const float &dt);
	// check and act upon collision with mario
	void killorDie(Character& mario);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};