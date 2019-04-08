#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Resources.h"

class Character : public sf::Drawable {
private:
	/*DISPLAY*/
		sf::Sprite sprite;

	/*PHYSICS*/
		sf::FloatRect lastBounds; // contains the bounds from one frame before the time taken
		bool jumpToggle; // used to disallow jumping in the air
		bool isJumping; // true whenever mario jumps. false when touches ground. used for animation
		float jumpVelocity; // the speed at which mario jumps
		float gForce; // gravity force applied at a given frame

	/*MOVEMENT ANIMATION*/
		bool flipOrient; // if true flips texture orientation (true means left, false means right)
		unsigned animationFrame; // 0-idle 1,2,3-running_cycle 4-brake 5-jump 6-death jump
		float animationTimer; // the timer used to measure time passed while running smoothly
		const float animationLimit = 0.12f; // the frequency in seconds at which movement animation works
		const sf::Vector2i animation[7] = { {13,16}, {14,16}, {12,16}, {16,16}, {14,16}, {17,16}, {15,14} }; // contains the sizes for each frame of animation
		sf::Vector2i animationPlace(const unsigned &index); // calculates the place of a texture in file
	/*DEATH ANIMATION*/
		bool isAlive; // used only for animation]
		bool lifeSignal; // used to communicate death after all animations ended
	/*INVULNERABLE ANIMATION*/
		float invATimer; // invulnerability animation timer
		const float invALimit = 0.1f; // the frequency in seconds at which flickering animation works
		bool isVisible; // used to display invulnerability

	/*CONTROLS*/
		sf::Keyboard::Key up = sf::Keyboard::Up; // key used for jumping
		sf::Keyboard::Key down = sf::Keyboard::Down; // key used for crouching
		sf::Keyboard::Key left = sf::Keyboard::Left; // key used for moving left
		sf::Keyboard::Key right = sf::Keyboard::Right; // key used for moving right

	/*PROPERTIES*/
		int lives; // lives remaining
		bool isInvulnerable; // true whenever mario is unkillable
		float invTimer; // invulnerability availability timer

	/* ALL IMPORTANT BOOLS GET INITIALIZED IN void setDefaultValues()*/
public:
	Character() {
		sprite.setTexture(Resources::mario_smallT); // default texture used
		sprite.setScale({ 6,6 }); // scales things to FHD render space
	}

	/*DRAWING*/
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	/*USER INTERACTIONS*/
	/* ! Should not be put into the events loop
	 Values are: delta time(elapsed time), gravity*/
	void controls(float dt, float gravity);

	/*IN-GAME INTERACTIONS*/
	// Should always be after controls
	void collidesWith(const sf::FloatRect &object);
	// Should always be after collision checks
	void animate(const float &dt);
	// called whenever enemies collide with character
	void hurt();

	/*SETTERS*/
	// sets up (and resets) default values of character and sets its position (usually used in setup)
	void initializeIn(const sf::Vector2f& position);
	// changes default texture used
	void changeTexture(const sf::Texture& texture);
	// changes the way the character gets controlled
	void changeCntrlKeys(const sf::Keyboard::Key& in_up,
		const sf::Keyboard::Key& in_down,
		const sf::Keyboard::Key& in_left,
		const sf::Keyboard::Key& in_right);

	/*GETTERS*/
	// returns the global bounds of the object at a given time
	sf::FloatRect getGlobalBounds() const { return sprite.getGlobalBounds(); }
	// returns the penultimate global bounds of the object
	sf::FloatRect getLastBounds() const { return lastBounds; }
	// returns how many lives the character has
	int getlifeSignal() const { return lifeSignal; }
};