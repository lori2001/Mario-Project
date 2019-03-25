#pragma once
#include "SFML/Graphics.hpp"
#include "Resources.h"
#include "Mario.h"
#include "Ground.h"

class Game {
private:
	Resources resources;

	Mario mario;
	Ground ground;

	const float gravity = 5; // the global value of the gravity

	// used at making movement non-time reliant
	sf::Clock clock;
	float elapsedTime;

public:
	bool isActive = true;

	void Setup(sf::RenderWindow &window);
	// void handleEvents(const sf::Event &event);
	void Update(sf::RenderWindow &window);
	void Compose(sf::RenderWindow &window) const;
};