#pragma once
#include "SFML/Graphics.hpp"
#include "Paths.h"
#include "Mouse.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

/* this is an impossible position value which can be checked against
   to find out if one of the characters was not declared */
static constexpr float notfound = -9999.99f;

struct inOutObj {
	inOutObj(const sf::Vector2f& in_pos, const float in_scale, const int in_size = 0) {
		pos = in_pos;
		scale = in_scale;
		size = in_size;
	}

	sf::Vector2f pos; // the top-left position of the object
	float scale; // the scale of the object

	int size; // the width (in nr of entities) of the object / only for brick and grounds
};

class ReadWrite
{
public:
	static void readMap();
	static void saveMap();
	static void uploadObj(const std::vector<sf::RectangleShape> &obj, const std::vector<int> &objType);

private:
	static sf::Vector2f mapLength;
	static inOutObj character1;
	static inOutObj character2;
	static inOutObj endpoint;
	static std::vector<inOutObj> enemies;
	static std::vector<inOutObj> healers;
	static std::vector<inOutObj> bricks;
	static std::vector<inOutObj> grounds;
	static std::vector<inOutObj> coins;

	// resets variables whenever reading maps
	static void resetVariables();
	/* clears input from comments, empty lines and unnecessary spaces
	   returns 1 if all is ok, 0 if something is wrong, any other number if nothing has to happen */
	static int clearInput(std::string &input);

public:
	// getters and setters for the length of the map
	static sf::Vector2f getMapLength() { return mapLength; };
	static void setMapLength(sf::Vector2f param) { mapLength = param; };

	// returns the position character1 should be initialized in
	static inOutObj getCharacter1() { return character1; }
	// returns the position character2 should be initialized in
	static inOutObj getCharacter2() { return character2; }
	// returns the position endpoint should be put in
	static inOutObj getEndpoint() { return endpoint; }

	// returns the position of an enemy at a given index
	static inOutObj getEnemy(int i) { return enemies[i]; }
	// returns the number of enemies
	static int getEnemiesNum() { return int(enemies.size()); }

	// returns the position of a healer at a given index
	static inOutObj getCoin(int i) { return coins[i]; }
	// returns the number of healers
	static int getCoinsNum() { return int(coins.size()); }

	// returns the position of a healer at a given index
	static inOutObj getHealer(int i) { return healers[i]; }
	// returns the number of healers
	static int getHealersNum() { return int(healers.size()); }

	// returns the position of a brick at a given index (x,y - positions; z-size)
	static inOutObj getBrick(int i) { return bricks[i]; }
	// returns the number of bricks
	static int getBricksNum() { return int(bricks.size()); }

	// returns the position of a ground at a given index (x,y - positions; z-size)
	static inOutObj getGround(int i) { return grounds[i]; }
	// returns the number of grounds
	static int getGroundsNum() { return int(grounds.size()); }
};