#include "Ground.h"

void Ground::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite);
}
