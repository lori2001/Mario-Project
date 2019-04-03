#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Resources.h"

class Mario : public sf::Drawable {
private:
	/*DISPLAY*/
	sf::Sprite sprite;

	/*PHYSICS*/
	sf::FloatRect lastBounds; // contains the bounds from one frame before the time taken
	bool jumpToggle = false; // used to disallow jumping in the air
	bool isJumping = true; // true whenever mario jumps. false when touches ground. used for animation
	float jumpVelocity = 0; // the speed at which mario jumps
	float gForce = 0; // gravity force applied at a given frame

	/*ANIMATION*/
	bool flipOrient = false; // if true flips texture orientation (true means left, false means right)
	unsigned animationFrame = 1; // 0-idle
	float animationTimer = 0; // the timer used to measure time passed while running smoothly
	float animationLimit = 0.12f; // the frequency in seconds at which movement animation works
	sf::Vector2i animation[7] = { {13,16}, {14,16}, {12,16}, {16,16}, {14,16}, {17,16}, {15,14} }; // contains the sizes for each frame of animation
	sf::Vector2i animationPlace(const unsigned &index); // calculates the place of a texture in file
		/*death animation*/
		bool isAlive = true;
public:
	Mario() {
		sprite.setTexture(Resources::mario_smallT); // default texture used
		sprite.setScale({ 6,6 }); // scales things to FHD render space
	}

	// ! Should not be put into the events loop
	void controls(const float &dt, const float &gravity);
	// Should always be after controls
	void collidesWith(const sf::FloatRect &object);
	// Should always be after collision checks
	void animate(const float &dt);

	void kill();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	// settters
	void setPosition(const sf::Vector2f& position);

	// getters
	// returns the global bounds of the object at a given time
	sf::FloatRect getGlobalBounds() const { return sprite.getGlobalBounds(); }
	// returns the penultimate global bounds of the object
	sf::FloatRect getLastBounds() const { return lastBounds; }
};