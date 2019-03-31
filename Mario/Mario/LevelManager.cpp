#include "LevelManager.h"

int LevelManager::run(sf::RenderWindow &window)
{
	// applies view to window
	window.setView(view);
	
	// window setup
	window.setIcon(Resources::icon.getSize().x, Resources::icon.getSize().y, Resources::icon.getPixelsPtr()); // sets icon to sfml window

	// setup positions/sizes/etc.
	menu.Setup(window);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			menu.handleEvents(window, event);

			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color(100, 100, 250)); // the background used in-game

		if (menu.getActive()) {
			// contains frame-by-frame logic
			menu.Update(window);
			// contains drawing commands
			menu.Compose(window);

			if (menu.getActive() == false) {
				game.setActive(true);
				game.Setup(window);
			}
		}
		else if (game.getActive()) {
			// contains frame-by-frame logic
			game.Update(window);
			// contains drawing commands
			game.Compose(window);
		}

		window.display();
	}

	return 0;
}
