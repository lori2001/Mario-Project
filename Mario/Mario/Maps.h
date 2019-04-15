#pragma once
#include "SFML/System.hpp"
#include <vector>
#include <fstream>
#include <iostream>
#include <assert.h>
#include <sstream>

/* this is an impossible position value which can be checked against 
   to find out if one of the characters was not declared */
static constexpr float notfound = -9999.99f;

class Maps
{
private:
	static std::vector<std::string> maps;
	static sf::Vector2f character1;
	static sf::Vector2f character2;
	static std::vector<sf::Vector2f> enemies;
	static std::vector<sf::Vector2f> healers;

	// x and y are the positions, z is its size
	static std::vector<sf::Vector3f> bricks;
	// x and y are the positions, z is its size
	static std::vector<sf::Vector3f> grounds;

	// clears variables whenever reading maps
	static void clearVariables();
public:
	// returns the position character1 should be initialized in
	static sf::Vector2f getCharacter1() { return character1; }
	// returns the position character2 should be initialized in
	static sf::Vector2f getCharacter2() { return character2; }

	// returns the position of an enemy at a given index
	static sf::Vector2f getEnemy(int i) { return enemies[i]; }
	// returns the number of enemies
	static int getEnemiesNum() { return int(enemies.size()); }

	// returns the position of a healer at a given index
	static sf::Vector2f getHealer(int i) { return healers[i]; }
	// returns the number of healers
	static int getHealersNum() { return int(healers.size()); }

	// returns the position of a brick at a given index (x,y - positions; z-size)
	static sf::Vector3f getBrick(int i) { return bricks[i]; }
	// returns the number of bricks
	static int getBricksNum() { return int(bricks.size()); }

	// returns the position of a ground at a given index (x,y - positions; z-size)
	static sf::Vector3f getGround(int i) { return grounds[i]; }
	// returns the number of grounds
	static int getGroundsNum() { return int(grounds.size()); }

	static void readList();
	static void readMap(int mapnumber);
};