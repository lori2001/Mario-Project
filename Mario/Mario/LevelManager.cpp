#include "LevelManager.h"

int LevelManager::run(sf::RenderWindow &window)
{
	// applies view to window
	window.setView(view);

	// for testing
	//window.setFramerateLimit(20);

	// setup positions/sizes/etc.
	// make mainmenu the first screen to see
	mainmenu.Setup();

	Maps::readList();
	Maps::readMap(0);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (!mainmenu.getStartGame()) {
				mainmenu.handleEvents(window, event);
			}
			else if (gameover.getisActive()) {
				gameover.handleEvents(window, event);
			}
			else if (gamewon.getisActive()) {
				gamewon.handleEvents(window, event);
			}

			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color(92, 148, 252)); // the background used in-game

		// if game didn't start yet, show mainmenu
		if (!mainmenu.getStartGame()) {
			mainmenu.Update(window);
			mainmenu.Compose(window);

			// if game is started
			if (mainmenu.getStartGame()) {
				game.Setup(); // setup(start) game
			}
		}
		else if (game.getisActive()) { // if game is playing
			// contains game logic
			game.Update(view);
			// contains game drawing
			game.Compose(window);

			// update viewport whenever needed
			window.setView(view);

			if (!game.getisActive() && game.getisWon()) // if ended and won
			{
				if (Maps::getSelectedMap() + 1 < Maps::getMapsNum()) {
					gamewon.Setup(false); // false bc not fully won
				}
				else {
					Maps::readMap(0); // reset map to first one
					gamewon.Setup(true); // true because the entire game has been finished
				}

				// reset viewport position
				view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
				window.setView(view);
			}
			else if (!game.getisActive()) { // if ended but not won
				gameover.Setup();

				// reset viewport position
				view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
				window.setView(view);
			}
		
		}
		else if (gamewon.getisActive()) { // game won screen
			gamewon.Update();
			gamewon.Compose(window);

			if (!gamewon.getisActive() && !gamewon.getContinue()) {
				mainmenu.Setup(); // go back to menu
			}
			else if (!gamewon.getisActive()) {
				Maps::readMap(Maps::getSelectedMap() + 1); // read the next map
				game.Setup(); // go to game (should go to next map)
				Resources::themesongM.play(); // play theme song again
			}
		}
		else if(gameover.getisActive()) { // game over screen
			gameover.Update(window);
			gameover.Compose(window);

			// if gameover is disabled but still in game
			if (!gameover.getisActive()) {
				mainmenu.Setup();
				Maps::readMap(0); // reset map
			}
		}

		window.display();
	}

	return 0;
}
