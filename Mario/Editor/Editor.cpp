#include "Editor.h"

int Editor::run(sf::RenderWindow &window)
{
	// applies view to window
	window.setView(view);
	
	// window setup
	// window.setIcon(Resources::icon.getSize().x, Resources::icon.getSize().y, Resources::icon.getPixelsPtr()); // sets icon to sfml window

	// for testing
	//window.setFramerateLimit(20);

	// setup positions/sizes/etc.

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color(100, 100, 250)); // the background used in-game
		window.display();
	}

	return 0;
}
