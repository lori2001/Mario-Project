#include "Program.h"

int Program::run(sf::RenderWindow &window)
{
	// applies view to window
	window.setView(view);

	userInterface.Setup();

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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && view.getCenter().x > view.getSize().x / 2) {
			view.move(-5,0);

			// block view at the leftmost side
			if (view.getCenter().x < view.getSize().x / 2) {
				view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
			}
			window.setView(view);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			view.move(5, 0);
			window.setView(view);
		}

		userInterface.Update(view);
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
