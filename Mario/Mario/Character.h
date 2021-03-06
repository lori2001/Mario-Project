#pragma once
#include <iostream>
#include <vector>

#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"

#include "Maps.h"
#include "Resources.h"
#include "Ground.h"

class Character : public sf::Drawable {
private:
	/*DISPLAY*/
		sf::Sprite sprite;
		std::vector<sf::Sprite> hearts; // used to display number of lives
		sf::Vector2f heartspos{20,20}; // the position of the first heart on the string
		const sf::Vector2f heartoffset{ 40,0 }; // the distance between each heart

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
		const sf::Vector2i animationSizes[7] = { {13,16}, {14,16}, {12,16}, {16,16}, {14,16}, {17,16}, {15,14} }; // contains the sizes for each frame of animation
		sf::Vector2i animationPlace(const unsigned &index); // calculates the place of a texture in file
	/*DEATH ANIMATION*/
		bool isAlive; // used only for animation
		bool lifeSignal; // used to communicate death after all animations ended
	/*INVULNERABLE ANIMATION*/
		float invATimer; // invulnerability animation timer
		const float invALimit = 0.1f; // the frequency in seconds at which flickering animation works
		bool isVisible; // used to display invulnerability

	/*CONTROLS*/
		sf::Keyboard::Key up; // key used for jumping
		sf::Keyboard::Key down; // key used for crouching
		sf::Keyboard::Key left; // key used for moving left
		sf::Keyboard::Key right; // key used for moving right

	/*PROPERTIES*/
		int lives; // lives remaining
		bool isInvulnerable; // true whenever mario is unkillable
		float invTimer; // invulnerability availability timer

	/*SOUND*/
		sf::Sound jumpSound; // the sound played whenever jumping

	/* ALL IMPORTANT BOOLS GET INITIALIZED IN void setDefaultValues()*/
public:
	Character(float scale = 6) {
		jumpSound.setBuffer(Resources::jumpSB);

		sprite.setTexture(Resources::mario_smallT); // default texture used
		sprite.setScale({ scale,scale }); // scales things to FHD render space
	}

	/*DRAWING*/
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	/*USER INTERACTIONS*/
	/* ! Should not be put into the events loop
	 Values are: delta time(elapsed time), gravity, view-positions*/
	void movement(float dt, float gravity, sf::View& view);

	/*IN-GAME INTERACTIONS*/
	/*Takes in Ground and its child classes*/
	void collision(Ground& object);
	// animates the movement of the character
	void animation(const float dt);
	// called whenever enemies should hurt character
	bool hurt();
	// called whenever healers should heal character
	bool heal();

	/*SETTERS*/
	// sets up (and resets) default values of character and sets its position (usually used in setup)
	void initializeIn(const sf::Vector2f& position, const float scale);
	// changes default texture used
	void changeTexture(const sf::Texture& texture);
	// !IMPORTANT! sets the way the character gets controlled
	void setCntrlKeys(const sf::Keyboard::Key& in_up,
		const sf::Keyboard::Key& in_down,
		const sf::Keyboard::Key& in_left,
		const sf::Keyboard::Key& in_right);
	// changes the place where lives will be displayed
	void changeHeartsPos(const sf::Vector2f& position);
	// basically makes mario jump
	void jump(const unsigned velocity);
	// called whenever character is not declared
	void doNotDisplay();

	/*GETTERS*/
	// returns the global bounds of the object at a given time
	sf::FloatRect getGlobalBounds() const { return sprite.getGlobalBounds(); }
	// returns the penultimate global bounds of the object
	sf::FloatRect getLastBounds() const { return lastBounds; }
	// returns how many lives the character has
	int getlifeSignal() const { return lifeSignal; }
	// returns position of mario (top left corner)
	sf::Vector2f getPosition() { return sprite.getPosition(); }
	void setVisibility(bool param) { isVisible = param; }
	// walks right with given speed
	void walkRight(const float speed) { 
		flipOrient = false;
		lastBounds = sprite.getGlobalBounds();
		sprite.move({speed,0});
	}
	// !!!WARNING values get lost once disabled!!!
	void disableKeys() {
		up = sf::Keyboard::Unknown;
		down = sf::Keyboard::Unknown;
		left = sf::Keyboard::Unknown;
		right = sf::Keyboard::Unknown;
	}
};