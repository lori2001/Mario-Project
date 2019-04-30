#include <SFML/Graphics.hpp>
#include "Paths.h"
#include "Resources.h"
#include "Program.h"

int main()
{
	// creates and sets window's default sizes and name
	sf::RenderWindow window{ sf::VideoMode{1000, 600 }, "Mario Map Editor", sf::Style::Titlebar | sf::Style::Close };

	// load and set the icon file
	sf::Image icon;
	icon.loadFromFile("edicon.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr()); // sets icon to sfml window

	// try to load files in the current directory
	Paths::setGamePath("");
	if (!Resources::loadFiles(window)) { // if fail -> open using file dialog
		if (!Paths::chooseGamePath()) // close program if no path is selected
		{
			return 0;
		}
		Resources::loadFiles(window);
	}

	Program program;
	return program.run(window);
}