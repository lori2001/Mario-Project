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
	static constexpr int coinID = 6;
	static constexpr int eraserID = 7;

	static void setSelected(int param) { selected = param; }
	static int getSelected() { return selected; }

	// if false mouse object won't be drawn
	void setDrawing(bool param) { drawing = param; }
	bool getDrawing() const { return drawing; }

	void updateObject();
private:
	static int selected;

	int lastSelected = -1; // there is none selected by default
	bool drawing = false;
	float scale = 1.0f;
};