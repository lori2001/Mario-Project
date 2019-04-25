#include "Program.h"

int Program::run(sf::RenderWindow &window)
{
	// applies view to window
	window.setView(view);

	userInterface.Setup(window);
	// editor.Setup(window);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			userInterface.handleEvents(window, event);
			editor.handleEvents(window, event);
		}

		window.clear(sf::Color(100, 100, 250)); // the background used in-game

		userInterface.Update(window);
		userInterface.Compose(window);

		if (userInterface.opening)
		{
			editor.loadMap();
			userInterface.opening = false;
		}
		else if (userInterface.saveing) {
			editor.saveMap();
			userInterface.saveing = false;
		}

		editor.Update(window);
		editor.Compose(window);

		window.display();
	}

	return 0;
}
