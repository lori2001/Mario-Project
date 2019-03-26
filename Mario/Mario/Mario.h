#pragma once
#include "SFML/Graphics.hpp"

class Mario : public sf::Drawable {
private:
	sf::Sprite sprite;
	
	sf::FloatRect lastBounds;

	bool inAir = false;
	float timeStep = 0;
	float jumpVelocity = 0;
	float gForce = 0;
public:
	void setPosition(const sf::Vector2f& position);
	void setScale(const sf::Vector2f& scale);
		void setScale(const float &scale) { this->setScale({ scale,scale }); }
	void setTexture(const sf::Texture& texture);

	// ! Should not be put into the events loop
	void controls(const float &dt, const float &gravity);
	void collidesWith(const sf::FloatRect &object);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};