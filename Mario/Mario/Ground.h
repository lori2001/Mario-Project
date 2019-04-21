#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Resources.h"

class Ground : public sf::Drawable
{
protected:
	std::vector<sf::RectangleShape> shapes;
	sf::Texture *texture = &Resources::groundT;
	sf::Vector2f position;

	bool canMove = false; // set this to true to make item moveable
	bool canBreak = false; // NOT YET IMPLEMENTED set this to true to make item breakable
private:
	std::vector<bool> isMoving; // bool to signal whether a ground brick is moving or not
	std::vector<bool> isActive;

	float yPos; // holds the y pos of the shape to be able to reset to it whenever needed
	std::vector<float> animationTimer; // the timer used to measure time passed while running smoothly
	const float animationLimit = 0.001f; // the frequency in seconds at which movement animation works
	std::vector<float> movementOffset; // the offset count per ground brick (-1 means nothing)
	const float offsetLimit = 15; // the number of pixels a hit ground should offset to
	std::vector<bool> movingUp; // true whenever moving up, false whenever moving down
public:
	// x and y are coordinates while z is the lenght in ground bricks
	void initializeIn(const sf::Vector2f &pos, const float scale, const int size);

	Ground(const sf::Vector2f& pos, const float scale, const int size) {
		initializeIn(pos, scale, size);
	}
	Ground(const int size) : Ground({ 0, 0 }, 4.5f , size) {}
	Ground() : Ground(1) {}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	/*triggered by canMove*/
	void moveIfShould(const int i);
	void animation(const float dt);

	// getters
	sf::FloatRect getGlobalBounds(const int i) { return shapes[i].getGlobalBounds(); }
	int getRowSize() { return int(shapes.size()); }
};
