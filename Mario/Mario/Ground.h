#pragma once
#include <SFML/Graphics.hpp>
#include "Resources.h"

class Ground : public sf::Drawable
{
private:
	sf::RectangleShape sprite;
public:
	Ground() {
		sprite.setFillColor(sf::Color::Yellow);
		sprite.setPosition({ 0, (float)HEIGHT - 50 });
		sprite.setSize({ (float)WIDTH, 50});
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
