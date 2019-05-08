#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Resources.h"
#include "Character.h"
#include "Score.h"

class Endpoint : public sf::Drawable {
public:
	Endpoint(const sf::Vector2f& position, const float scale = 4) {
		castle.setTexture(Resources::castle_smallT);
		flag.setTexture(Resources::flagT);

		initializeIn(position, scale);
	}
	Endpoint() : Endpoint(sf::Vector2f{0, 0}) {}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	// sets up (and resets) default values of endpoint and places it in position
	void initializeIn(const sf::Vector2f& position, const float scale);

	// check and act IMMEDIATELY upon collision with character
	void detection(Character& character, const float dt);

private:
	sf::Sprite castle;
	sf::Sprite flag;

	/*PROPERTIES*/
	bool animationTrigger; // triggers animation and signals the (happy)ending of the game
	bool gameWon; // if true goes out to gameWon menu
	float nonSoundWin; // acts as an emergency exit in case there is no audio card in the PC

	/*ANIMATION*/
	sf::Vector2f animPos; // the position which has to be reached by the flag
	sf::FloatRect animBounds; // chops width of object to make it look better
	
public:
	/*GETTERS / SETTERS*/
	sf::FloatRect getGlobalBounds() { return castle.getGlobalBounds(); }

	// returns true whenever game is won
	bool getWillWin() { return animationTrigger; }
	bool getGameWon() { return gameWon; }
};
