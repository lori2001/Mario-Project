#include "Ground.h"

void Ground::initializeIn(const sf::Vector2f& pos, const float scale,const int size)
{
	position = { pos.x , pos.y };
	yPos = position.y;
	playBump = true;

	while (int(size) > int(shapes.size())) {
		isActive.push_back(true);
		isMoving.push_back(false);
		movingUp.push_back(true);
		animationTimer.push_back(0);
		movementOffset.push_back(0);
		shapes.push_back(sf::RectangleShape{});
	}

	for (int i = 0; i < int(size); i++) {
		isMoving[i] = false;
		isActive[i] = true;
		movingUp[i] = true;
		animationTimer[i] = 0;
		movementOffset[i] = 0;
		shapes[i].setTexture(texture);
		shapes[i].setSize(sf::Vector2f(float(Resources::groundT.getSize().x), float(Resources::groundT.getSize().y)));
		shapes[i].setScale({ scale, scale });
		shapes[i].setPosition(position.x + i * shapes[i].getGlobalBounds().width, position.y);
	}
}

void Ground::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (int i = 0; i < int(shapes.size()); i++) {
		if (isActive[i]) {
			target.draw(shapes[i]);
		}
	}
}

void Ground::moveIfShould(const int i)
{
	if (canMove) {
		isMoving[i] = true;
	}
}

void Ground::animation(const float dt)
{
	for (int i = 0; i < int(shapes.size()); i++) {
		if (isMoving[i]) {
			animationTimer[i] += dt;

			if (animationTimer[i] > animationLimit) {

				if (playBump && bumpSound.getStatus() != sf::Music::Status::Playing) {
					bumpSound.play();
					playBump = false;
				}

				if (movingUp[i] == true) {
					shapes[i].move(0, -150 * dt);
					movementOffset[i] += 150 * dt;
					playBump = true;
					if (movementOffset[i] >= offsetLimit) {
						movingUp[i] = false;
					}
				}
				else {
					shapes[i].move(0, 150 * dt);
					movementOffset[i] -= 150 * dt;
					if (movementOffset[i] <= 0) {
						movingUp[i] = true;
						isMoving[i] = false;
						shapes[i].setPosition(shapes[i].getPosition().x, yPos);
					}
				}

				animationTimer[i] = 0;
			}
		}
	}
}
