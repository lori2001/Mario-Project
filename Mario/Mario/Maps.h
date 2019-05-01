#pragma once
#include "SFML/System.hpp"
#include <vector>
#include <fstream>
#include <iostream>
#include <assert.h>

/* this is an impossible position value which can be checked against 
   to find out if one of the characters was not declared */
static constexpr float notfound = -9999.99f;

struct inputObject {
	inputObject(const sf::Vector2f& in_pos, const float in_scale, const int in_size = 0) {
		pos = in_pos;
		scale = in_scale;
		size = in_size;
	}

	sf::Vector2f pos; // the top-left position of the object
	float scale; // the scale of the object

	int size; // the width (in nr of entities) of the object / only for brick and grounds
};

class Maps
{
private:
	static float mapLength;
	static std::vector<std::string> maps;
	static inputObject character1;
	static inputObject character2;
	static inputObject endpoint;
	static std::vector<inputObject> enemies;
	static std::vector<inputObject> healers;
	static std::vector<inputObject> bricks;
	static std::vector<inputObject> grounds;
	static std::vector<inputObject> coins;

	// resets variables whenever reading maps
	static void resetVariables();
	/* clears input from comments, empty lines and unnecessary spaces
	   returns 1 if all is ok, 0 if something is wrong, any other number if nothing has to happen */
	static int clearInput(std::string &input);

public:
	// returns the length of the map
	static float getMapLength() { return mapLength;  }

	// returns the position character1 should be initialized in
	static inputObject getCharacter1() { return character1; }
	// returns the position character2 should be initialized in
	static inputObject getCharacter2() { return character2; }
	// returns the position endpoint should be placed in
	static inputObject getEndpoint() { return endpoint; }

	// returns the position of an enemy at a given index
	static inputObject getEnemy(int i) { return enemies[i]; }
	// returns the number of enemies
	static int getEnemiesNum() { return int(enemies.size()); }

	// returns the position of a healer at a given index
	static inputObject getHealer(int i) { return healers[i]; }
	// returns the number of healers
	static int getHealersNum() { return int(healers.size()); }

	// returns the position of a brick at a given index (x,y - positions; z-size)
	static inputObject getBrick(int i) { return bricks[i]; }
	// returns the number of bricks
	static int getBricksNum() { return int(bricks.size()); }

	// returns the position of a ground at a given index (x,y - positions; z-size)
	static inputObject getGround(int i) { return grounds[i]; }
	// returns the number of grounds
	static int getGroundsNum() { return int(grounds.size()); }

	// returns the position of a coin at a given index (x,y - positions; z-size)
	static inputObject getCoin(int i) { return coins[i]; }
	// returns the number of grounds
	static int getCoinsNum() { return int(coins.size()); }

	static void readList();
	static void readMap(int mapnumber);
};