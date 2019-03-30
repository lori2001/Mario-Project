#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Game.h"
#include "Resources.h"

// Program creat pentru IBSA 2019 de Szoke Andras Lorand

// in theory this gets disabled on other OS such as linux
// thus the program should run on all platforms !!! IN THEORY !!!
#ifdef _WIN32
	#include <Windows.h>
#endif
#ifdef _DEBUG
	#include <iostream>
#endif

int main()
{
	// hides console window on windows, release mode
	#ifdef _WIN32
		#ifndef _DEBUG
			HWND hWnd = GetConsoleWindow();
			ShowWindow(hWnd, SW_HIDE);
		#endif
	#endif

	//load icon file
	sf::Image icon;
	icon.loadFromFile("icon.png");

	// creates and sets window's default sizes and name
	sf::RenderWindow window(sf::VideoMode(1000, 600), "Mario");
	window.setFramerateLimit(24);
	
	sf::View view(sf::FloatRect(0, 0, 1920, 1080));
	window.setView(view); // Scales down 1920x1080 screen to whatever resolution needed

	//sets icon to sfml window
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	// loads all files needed
	Resources resources;
	resources.loadFiles(window);

	Game game;
	// setup positions/sizes/etc.
	game.Setup(window);

	Menu menu;
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

		// TODO: Fix this shit!!
		if (menu.getActive()) {
			// contains frame-by-frame logic
			menu.Update(window);
			// contains drawing commands
			menu.Compose(window);
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