#include "LevelManager.h"

int LevelManager::run(sf::RenderWindow &window)
{
	// applies view to window
	window.setView(view);
	
	// window setup
	window.setIcon(Resources::icon.getSize().x, Resources::icon.getSize().y, Resources::icon.getPixelsPtr()); // sets icon to sfml window

	// for testing
	//window.setFramerateLimit(20);

	// setup positions/sizes/etc.
	mainmenu.Setup(window);

	Maps::readList();
	Maps::readMap(0);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (mainisActive) {
				mainmenu.handleEvents(window, event);
			}
			else if (endscisActive) {

			}

			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color(100, 100, 250)); // the background used in-game

		if (mainisActive) {
			// contains frame-by-frame logic
			mainmenu.Update(window, mainisActive);
			// contains drawing commands
			mainmenu.Compose(window);

			if (!mainisActive) {
				gameisActive = true;
				game.Setup(window);
			}
		}
		else if (gameisActive) {
			// contains frame-by-frame logic
			game.Update(window, gameisActive);
			// contains drawing commands
			game.Compose(window);

			if (!gameisActive) {
				mainisActive = true;
			}
		}

		window.display();
	}

	return 0;
}
