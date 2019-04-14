#include <SFML/Graphics.hpp>
#include "Resources.h"
#include "LevelManager.h"

// in theory this gets disabled on other OS such as linux
// thus the program should compile on all platforms !!! IN THEORY !!!
#ifdef _WIN32
	#include <Windows.h>
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

	sf::RenderWindow window{ sf::VideoMode{1000, 600 }, "Mario" }; // creates and sets window's default sizes and name

	Resources::loadFiles(window);

	LevelManager levelManager;
	return levelManager.run(window);
}