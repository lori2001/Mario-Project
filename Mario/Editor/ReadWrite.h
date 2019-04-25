#pragma once
#include "SFML/Graphics.hpp"
#include "Paths.h"
#include "Mouse.h"
#include <vector>
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
private:
	static inOutObj character1;
	static inOutObj character2;
	static std::vector<inOutObj> enemies;
	static std::vector<inOutObj> healers;
	static std::vector<inOutObj> bricks;
	static std::vector<inOutObj> grounds;

	// resets variables whenever reading maps
	static void resetVariables();
	/* clears input from comments, empty lines and unnecessary spaces
	   returns 1 if all is ok, 0 if something is wrong, any other number if nothing has to happen */
	static int clearInput(std::string &input);

public:
	// returns the position character1 should be initialized in
	static inOutObj getCharacter1() { return character1; }
	static void setCharacter1(const inOutObj& param) { character1 = param; }
	// returns the position character2 should be initialized in
	static inOutObj getCharacter2() { return character2; }
	static void setCharacter2(const inOutObj& param) { character2 = param; }

	// returns the position of an enemy at a given index
	static inOutObj getEnemy(int i) { return enemies[i]; }
	// returns the number of enemies
	static int getEnemiesNum() { return int(enemies.size()); }
	static void addEnemy(const inOutObj& param) { enemies.push_back(param); }

	// returns the position of a healer at a given index
	static inOutObj getHealer(int i) { return healers[i]; }
	// returns the number of healers
	static int getHealersNum() { return int(healers.size()); }
	static void addHealer(const inOutObj& param) { healers.push_back(param); }

	// returns the position of a brick at a given index (x,y - positions; z-size)
	static inOutObj getBrick(int i) { return bricks[i]; }
	// returns the number of bricks
	static int getBricksNum() { return int(bricks.size()); }
	static void addBrick(const inOutObj& param) { bricks.push_back(param); }

	// returns the position of a ground at a given index (x,y - positions; z-size)
	static inOutObj getGround(int i) { return grounds[i]; }
	// returns the number of grounds
	static int getGroundsNum() { return int(grounds.size()); }
	static void addGround(const inOutObj& param) { grounds.push_back(param); }

	static void readMap();
	static void saveMap();
	static void uploadObj(const std::vector<sf::RectangleShape> &obj, const std::vector<int> &objType);
};