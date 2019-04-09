#pragma once
#include "SFML/Graphics.hpp"
#include "Resources.h"
#include "Character.h"
#include "Ground.h"
#include "Enemy.h"
#include "Healer.h"

class Game {
private:
	Resources resources;

	Character mario;
	Character luigi;
	Ground ground1{ 19,1 };
	Ground ground3{ 8,1 };

	Enemy enemy1;
	Healer healer;

	const float gravity = 3500; // the global value of the gravity

	// used at making movement non-time reliant
	sf::Clock clock;
	float elapsedTime;
public:

	void Setup(sf::RenderWindow &window);
	// void handleEvents(const sf::Event &event);
	void Update(sf::RenderWindow &window, bool& isActive);
	void Compose(sf::RenderWindow &window) const;
};