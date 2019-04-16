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

	// initially go to menu and disable game
	mainmenu.setisActive(true);
	game.setisActive(false);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (mainmenu.getisActive()) {
				mainmenu.handleEvents(window, event);
			}
			else if (endscreen.getisActive()) {
				endscreen.handleEvents(window, event);
			}

			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color(100, 100, 250)); // the background used in-game

		if (mainmenu.getisActive()) {
			// contains frame-by-frame logic
			mainmenu.Update(window);
			// contains drawing commands
			mainmenu.Compose(window);

			if (!mainmenu.getisActive()) {
				game.setisActive(true);
				game.Setup(window);
			}
		}
		else if (game.getisActive()) {
			// contains frame-by-frame logic
			game.Update(window, view);
			// contains drawing commands
			game.Compose(window);

			// move viewport whenever needed
			window.setView(view);

			if (!game.getisActive()) {
				endscreen.setisActive(true);
				endscreen.Setup(window);

				// reset viewport position
				view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
				window.setView(view);
			}
		}
		else if(endscreen.getisActive()) {
			// contains frame-by-frame logic
			endscreen.Update(window);
			// contains drawing commands
			endscreen.Compose(window);

			if (!endscreen.getisActive()) {
				mainmenu.setisActive(true);
				mainmenu.Setup(window);
			}
		}

		window.display();
	}

	return 0;
}
