#include <SFML/Graphics.hpp>
#include "Paths.h"
#include "Resources.h"
#include "Program.h"

int main()
{
	sf::RenderWindow window{ sf::VideoMode{1000, 600 }, "Mario Map Editor" }; // creates and sets window's default sizes and name

	// load icon file
	sf::Image icon;
	icon.loadFromFile("icon.png");

	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr()); // sets icon to sfml window

	Paths paths;
	if (!paths.chooseGamePath()) // close program if no path is selected
	{
		return 0;
	}

	Resources resources;
	resources.loadFiles(window);

	Program program;
	return program.run(window);
}