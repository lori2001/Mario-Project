#include "Mouse.h"

int Mouse::selected;

void Mouse::changeScale(float offset)
{
	scale += offset;
	RectangleShape::setScale(sf::Vector2f{ scale, scale });
}

void Mouse::updateObject()
{
	if (selected != lastSelected)
	{
		RectangleShape::setFillColor(sf::Color::White); // reset eraser
		RectangleShape::setTexture(NULL);
		scale = 4.5f;

		if (selected == groundID) {
			RectangleShape::setTexture(&Resources::groundT);
			RectangleShape::setSize(sf::Vector2f{ Resources::groundT.getSize() });
			RectangleShape::setTextureRect({ 0, 0, int(Resources::groundT.getSize().x) , int(Resources::groundT.getSize().y) });
			scale = 2.25f;
		}
		else if (selected == brickID) {
			RectangleShape::setTexture(&Resources::brickT);
			RectangleShape::setSize(sf::Vector2f{ Resources::brickT.getSize() });
			RectangleShape::setTextureRect({ 0, 0, int(Resources::brickT.getSize().x) , int(Resources::brickT.getSize().y) });
			scale = 2.25f;
		}
		else if (selected == enemyID) {
			RectangleShape::setTexture(&Resources::enemy_mushT);
			RectangleShape::setSize(sf::Vector2f{ 16, 16 });
			RectangleShape::setTextureRect({ 0, 0, 16, 16 });
		}
		else if (selected == healerID) {
			RectangleShape::setTexture(&Resources::good_mushT);
			RectangleShape::setSize(sf::Vector2f{ Resources::good_mushT.getSize() });
			RectangleShape::setTextureRect({ 0, 0, int(Resources::good_mushT.getSize().x), int(Resources::good_mushT.getSize().y) });
			scale = 2.25f;
		}
		else if (selected == marioID) {
			RectangleShape::setTexture(&Resources::mario_smallT);
			RectangleShape::setSize(sf::Vector2f{ 13, 16 });
			RectangleShape::setTextureRect({ 0, 0, 13, 16 });
			scale = 5.0f;
		}
		else if (selected == luigiID) {
			RectangleShape::setTexture(&Resources::luigi_smallT);
			RectangleShape::setSize(sf::Vector2f{ 13, 16 });
			RectangleShape::setTextureRect({ 0, 0, 13, 16 });
			scale = 5.0f;
		}
		else if (selected == coinID) {
			RectangleShape::setTexture(&Resources::coinT);
			RectangleShape::setSize(sf::Vector2f{ 8, 14 });
			RectangleShape::setTextureRect({ 0, 0, 8, 14 });
		}
		else if (selected == endpointID) {
			RectangleShape::setTexture(&Resources::castle_smallT);
			RectangleShape::setSize(sf::Vector2f{ 177, 168 });
			RectangleShape::setTextureRect({ 0, 0, 177, 168 });
		}
		else if (selected == eraserID) {
			RectangleShape::setFillColor(sf::Color::Red);
			RectangleShape::setSize(sf::Vector2f{ 16, 16 });
		}

		lastSelected = selected;

		RectangleShape::setScale(sf::Vector2f{ scale, scale });
	}
}
