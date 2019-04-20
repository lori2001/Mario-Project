#include "Mouse.h"

int Mouse::selected;

void Mouse::updateObject()
{
	if (selected != lastSelected)
	{
		if (selected == groundID) {
			RectangleShape::setTexture(&Resources::groundT);
			RectangleShape::setSize(sf::Vector2f{ Resources::groundT.getSize() });
			RectangleShape::setTextureRect({ 0, 0, int(Resources::groundT.getSize().x) , int(Resources::groundT.getSize().y) });
			scale = 2.0f;
		}
		else if (selected == brickID) {
			RectangleShape::setTexture(&Resources::brickT);
			RectangleShape::setSize(sf::Vector2f{ Resources::brickT.getSize() });
			RectangleShape::setTextureRect({ 0, 0, int(Resources::brickT.getSize().x) , int(Resources::brickT.getSize().y) });
			scale = 2.0f;
		}
		else if (selected == enemyID) {
			RectangleShape::setTexture(&Resources::enemy_mushT);
			RectangleShape::setSize(sf::Vector2f{ 16, 16 });
			RectangleShape::setTextureRect({ 0, 0, 16, 16 });
			scale = 4.5f;
		}
		else if (selected == healerID) {
			RectangleShape::setTexture(&Resources::good_mushT);
			RectangleShape::setSize(sf::Vector2f{ 16, 16 });
			RectangleShape::setTextureRect({ 0, 0, 16, 16 });
			scale = 4.0f;
		}
		else if (selected == marioID) {
			RectangleShape::setTexture(&Resources::mario_smallT);
			RectangleShape::setSize(sf::Vector2f{ 13, 16 });
			RectangleShape::setTextureRect({ 0, 0, 13, 16 });
			scale = 6.0f;
		}
		else if (selected == luigiID) {
			RectangleShape::setTexture(&Resources::luigi_smallT);
			RectangleShape::setSize(sf::Vector2f{ 13, 16 });
			RectangleShape::setTextureRect({ 0, 0, 13, 16 });
			scale = 6.0f;
		}

		RectangleShape::setScale(sf::Vector2f{scale, scale});

		lastSelected = selected;
	}
}
