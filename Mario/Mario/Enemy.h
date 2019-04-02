#pragma once
#include "SFML/Graphics.hpp"
#include "Resources.h"

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
	/*bool flipOrient = false; // if true flips texture orientation (true means left, false means right)
	unsigned animationFrame = 1; // 0-idle
	float animationTimer = 0; // the timer used to measure time passed while running smoothly
	float animationLimit = 0.12f; // the frequency in seconds at which movement animation works
	// contains the sizes for each frame of animation
	sf::Vector2i animation[7] = { {13,16}, {14,16}, {12,16}, {16,16}, {14,16}, {17,16}, {15,14} };
	sf::Vector2i animationPlace(const unsigned &index); // calculates the place of a texture in file
	*/
public:
	Enemy() {
		sprite.setTexture(Resources::enemyT);
		sprite.setScale({1.7f,1.7f});
	}
	void setPosition(const sf::Vector2f& position);

	// ! Should not be put into the events loop
	void controls(const float &dt, const float &gravity);
	// Should always be after controls
	void collidesWith(const sf::FloatRect &object);
	// Should always be after collision checks
	// void animate(const float &dt);

	void kill(const sf::FloatRect &object, sf::RenderWindow& tmp);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};