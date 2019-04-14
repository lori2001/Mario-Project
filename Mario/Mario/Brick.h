#pragma once
#include "Ground.h"

class Brick : public Ground{
private:
public:
	Brick(const sf::Vector3f& pos_size) {
		texture = &Resources::brickT;
		canMove = true;
		canBreak = true; // no logic for this yet
		initializeIn(pos_size);
	}
	Brick(const int size) : Brick({ 0, 0, float(size) }) {}
	Brick() : Brick(1) {}
};