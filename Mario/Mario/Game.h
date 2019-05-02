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
#include "Coin.h"
#include "Endpoint.h"

class Game {
private:
	Score score;

	Character mario;
	Character luigi;
	Endpoint endpoint;

	std::vector<Enemy> enemies;
	std::vector<Healer> healers;
	std::vector<Coin> coins;
	std::vector<Brick> bricks;
	std::vector<Ground> grounds;

	const float gravity = 3500; // the global value of the gravity

	// used at making movement non-time reliant
	sf::Clock clock;
	float elapsedTime;

	bool isActive = false;
	bool isWon;
public:
	bool getisActive() const { return isActive; }
	bool getisWon() const { return isWon; }

	void Setup(sf::RenderWindow &window);
	// void handleEvents(const sf::Event &event);
	void Update(const sf::RenderWindow &window, sf::View &view);
	void Compose(sf::RenderWindow &window) const;
};