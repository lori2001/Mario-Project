#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include "Maps.h"
#include "Resources.h"
#include "Score.h"

#include "Character.h"
#include "Ground.h"
#include "Enemy.h"
#include "Healer.h"
#include "Brick.h"

class Game {
private:
	Score score;

	Character mario;
	Character luigi;

	std::vector<Ground> grounds;
	std::vector<Brick> bricks;
	std::vector<Enemy> enemies;
	std::vector<Healer> healers;

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