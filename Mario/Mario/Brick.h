#pragma once
#include "Ground.h"

class Brick : public Ground{
private:
public:
	Brick(const int size, const sf::Vector2f& position) {
		texture = &Resources::brickT;
		canMove = true;
		canBreak = true; // no logic for this yet
		initializeIn(size, position);
	}
	Brick(const int size) : Brick(size, { 0,0 }) {}
	Brick() : Brick(1) {}
};