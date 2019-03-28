#pragma once
#include <SFML/Graphics.hpp>
#include "Resources.h"

class Ground : public sf::Drawable
{
private:
	sf::Sprite sprite;
	sf::Vector2i size; // size as number of blocks
public:
	Ground(const sf::Vector2i &size) {
		this->size = size;
		sprite.setTexture(Resources::groundT);
		sprite.setTextureRect({ 0, 0,int(size.x * Resources::groundT.getSize().x), int(size.y *Resources::groundT.getSize().y) });
		sprite.setScale({2, 2});
	}
	Ground(const int &x, const int &y) : Ground(sf::Vector2i{x,y}) {}
	Ground() : Ground(1,1) {}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	// setters
	void setPosition(const sf::Vector2f &position) { sprite.setPosition(position); };

	// getters
	sf::FloatRect getGlobalBounds() { return sprite.getGlobalBounds(); }
};
