#pragma once
#include "SFML/Graphics.hpp"
#include "Resources.h"

class Mario : public sf::Drawable {
private:
	sf::Sprite sprite;
	
	sf::FloatRect lastBounds;

	/* default to true to avoid a bug
	   signals whenever mario is touching the ground (is flickering all the time due to the nature of the program)*/
	bool isJumping = true;
	float jumpVelocity = 0; // the speed ath which mario jumps
	float gForce = 0; // gravity force applied at a given frame

	bool flipOrient = false; // if true flips texture orientation (true means left, false means right)
	bool walkingAnim = false; // true whenever wawlking, false whenever standing
	float animationTimer = 0; // the timer used to measure time passed while running smoothly
	float animationLimit = 0.15f; // the frequency in seconds at which movement animation works 
public:
	Mario() {
		sprite.setTexture(Resources::mario_standT);
	}

	void setPosition(const sf::Vector2f& position);
	void setScale(const sf::Vector2f& scale);
		void setScale(const float &scale) { this->setScale({ scale,scale }); }

	// ! Should not be put into the events loop
	void controls(const float &dt, const float &gravity);
	// Should always be after controls
	void collidesWith(const sf::FloatRect &object);
	// Should always be after collision checks
	void animate(const float &dt);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};