#pragma once
#include "SFML/Graphics.hpp"
#include "Resources.h"
#include "Character.h"
#include "Ground.h"
#include "Enemy.h"

class Game {
private:
	Resources resources;

	Character mario1;
	Character mario2;
	Ground ground1{ 19,1 };
	Ground ground3{ 8,1 };

	Enemy enemy1;
	Enemy enemy2;

	const float gravity = 3500; // the global value of the gravity

	// used at making movement non-time reliant
	sf::Clock clock;
	float elapsedTime;

	bool isActive = false;
public:
	void setActive(const bool &active) { isActive = active; }
	bool getActive() const { return isActive; }

	void Setup(sf::RenderWindow &window);
	// void handleEvents(const sf::Event &event);
	void Update(sf::RenderWindow &window);
	void Compose(sf::RenderWindow &window) const;
};