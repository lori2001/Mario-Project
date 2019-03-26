#pragma once
#include "SFML/Graphics.hpp"
#include "Resources.h"

class Mario : public sf::Drawable {
private:
	sf::Sprite sprite;
	
	sf::FloatRect lastBounds;

	bool inAir = false; // true whenever mario is in the air
	float jumpVelocity = 0; // the speed ath which mario jumps
	float gForce = 0; // gravity force applied at a given frame
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

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};