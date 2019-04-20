#pragma once
#include "SFML/Graphics.hpp"
#include "Resources.h"

class Mouse : public sf::RectangleShape {
public:
	static constexpr int groundID = 0;
	static constexpr int brickID = 1;
	static constexpr int enemyID = 2;
	static constexpr int healerID = 3;
	static constexpr int marioID = 4;
	static constexpr int luigiID = 5;

	static void setSelected(int param) { selected = param; }
	static int getSelected() { return selected; }

	void updateObject();
private:
	static int selected;
	int lastSelected = -1; // there is none selected by default
	float scale = 1.0f; 
};