#pragma once
#include "SFML/Graphics.hpp"
#include "Resources.h"
#include "Button.h"
#include "Mouse.h"

class UserInterface
{
public:
	void Setup(sf::RenderWindow &window);
	void handleEvents(const sf::RenderWindow &window, const sf::Event &event);
	void Update(sf::RenderWindow &window);
	void Compose(sf::RenderWindow &window);

private:
	sf::Vector2f mouse;

	UI::Button save{ sf::Vector2f{Resources::save_iconT.getSize()} };
	UI::Button open{ sf::Vector2f{Resources::open_iconT.getSize()} };

	UI::Button ground{ sf::Vector2f{Resources::groundT.getSize()} };
	UI::Button brick{ sf::Vector2f{Resources::brickT.getSize()} };
	UI::Button enemy{ sf::Vector2f{16,16} };
	UI::Button healer{ sf::Vector2f{16,16} };
	UI::Button mario{ sf::Vector2f{13,16} };
	UI::Button luigi{ sf::Vector2f{13,16} };

	sf::RectangleShape background{ sf::Vector2f{1920,80} };
};
