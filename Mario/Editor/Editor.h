#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include "ReadWrite.h"
#include "Mouse.h"

class Editor {
public:
	Editor() {
		lengthMark.setSize({2, WIDTH});
		lengthMark.setOrigin({ 1, 0 });
		lengthMark.setFillColor(sf::Color::Red);
		lengthMark.setPosition(WIDTH, 0);
	}

	void loadMap();
	void saveMap();
	void handleEvents(const sf::RenderWindow &window, const sf::Event &event);
	void Update(sf::RenderWindow &window, const float dt);
	void Compose(sf::RenderWindow &window);
private:
	Mouse mouse;

	bool canLock = false; // used for multi-ground placing
	float viewPos = 0; // makes placing ground while moving view possible
	sf::Vector2i mouseLock; // holds mouse position for position locking

	sf::RectangleShape lengthMark;
	std::vector<sf::RectangleShape> objects;
	std::vector<int> objectsType;
};