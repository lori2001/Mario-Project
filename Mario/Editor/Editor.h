#pragma once
#include "SFML/Graphics.hpp"
#include "Mouse.h"

class Editor {
public:
	void Setup(sf::RenderWindow &window);
	void handleEvents(const sf::RenderWindow &window, const sf::Event &event);
	void Update(sf::RenderWindow &window);
	void Compose(sf::RenderWindow &window);
private:
	Mouse mouse;
};