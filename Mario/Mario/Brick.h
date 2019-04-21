#pragma once
#include "Ground.h"

class Brick : public Ground{
private:
public:
	Brick(const sf::Vector2f& pos, const float scale, int size) {
		texture = &Resources::brickT;
		canMove = true;
		canBreak = true; // no logic for this yet
		initializeIn(pos, scale , size);
	}
	Brick(const int size) : Brick({ 0, 0 }, 4.5f, size) {}
	Brick() : Brick(1) {}
};