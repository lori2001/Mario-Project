#include "Editor.h"

void Editor::Setup(sf::RenderWindow & window)
{
}

void Editor::handleEvents(const sf::RenderWindow & window, const sf::Event & event)
{
	mouse.setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
}

void Editor::Update(sf::RenderWindow & window)
{
	mouse.updateObject();
}

void Editor::Compose(sf::RenderWindow & window)
{
	window.draw(mouse);
}
