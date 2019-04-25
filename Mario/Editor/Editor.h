#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include "ReadWrite.h"
#include "Mouse.h"

class Editor {
public:
	void loadMap();
	void saveMap();
	void handleEvents(const sf::RenderWindow &window, const sf::Event &event);
	void Update(sf::RenderWindow &window);
	void Compose(sf::RenderWindow &window);
private:
	Mouse mouse;
	bool canLock = false;
	sf::Vector2i mouseLock;

	std::vector<sf::RectangleShape> objects;
	std::vector<int> objectsType;
};