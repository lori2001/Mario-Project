#pragma once
#include <SFML/Graphics.hpp>
#include "Resources.h"
#include <iostream>

class Ground : public sf::Drawable
{
public:
	sf::RectangleShape sprite;
public:

	sf::FloatRect getGlobalBounds() { return sprite.getGlobalBounds(); }
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
