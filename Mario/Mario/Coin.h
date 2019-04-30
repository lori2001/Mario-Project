#pragma once
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "Resources.h"
#include "Character.h"
#include "Score.h"

class Coin : public sf::Drawable {
private:
	/*DISPLAY*/
	sf::Sprite sprite;
	sf::Vector2f size{ 8, 14 };

	/*PROPERTIES*/
	bool isAlive; // false whenever taken

	/*ANIMATION*/
	sf::Vector2i animationPlace(const unsigned &index); // calculates the place of a texture in file
	int currFrame; // holds the number of the current frame of animation
	float animationTimer; // the timer used to measure time passed while running smoothly
	float animationLimit; // the frequency in seconds at which rotation animation works

	/*SOUND*/
	sf::Sound sound; // the sound played when coin is taken
public:
	Coin(const sf::Vector2f& position, const float scale = 4) {
		sound.setBuffer(Resources::coinSB);

		sprite.setTexture(Resources::coinT);
		// i don't like the original proportions :D
		sprite.setScale({ scale * 1.2f, scale });

		initializeIn(position);
	}
	Coin() : Coin({ 0,0 }) {}

	// sets up (and resets) default values of enemy and places it in position
	void initializeIn(const sf::Vector2f& position);

	// Animates coin rotation
	void animation(const float dt);

	// check and act upon collision with character
	void collision(Character& character);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};