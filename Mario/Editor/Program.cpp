#include "Program.h"

int Program::run(sf::RenderWindow &window)
{
	// applies view to window
	window.setView(view);

	userInterface.Setup();

	clock.restart();

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

		elapsedTime = clock.getElapsedTime().asSeconds();
		clock.restart();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && view.getCenter().x > view.getSize().x / 2) {
			view.move(-1500 * elapsedTime,0);

			// block view at the leftmost side
			if (view.getCenter().x < view.getSize().x / 2) {
				view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
			}
			window.setView(view);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			view.move(1500 * elapsedTime, 0);
			window.setView(view);
		}

		if (userInterface.opening)
		{
			editor.loadMap();
			userInterface.opening = false;
		}
		else if (userInterface.saveing) {
			editor.saveMap();
			userInterface.saveing = false;
		}

		editor.Update(window, elapsedTime);
		userInterface.Update(view);

		window.clear(sf::Color(100, 100, 250)); // the background used in-game

		editor.Compose(window);
		userInterface.Compose(window);

		window.display();
	}

	return 0;
}
