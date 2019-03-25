#pragma once
#include "SFML/Graphics.hpp"

class Mario : public sf::Drawable {
private:
	sf::Sprite sprite;

	float jumpVelocity = 0;
public:
	void setPosition(const sf::Vector2f& position);
	void setScale(const sf::Vector2f& scale);
		void setScale(const float &scale) { this->setScale({ scale,scale }); }
	void setTexture(const sf::Texture& texture);

	// ! Should not be put into the events loop
	void controls(const float &dt, const float &gravity);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};