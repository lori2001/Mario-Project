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

	// creates and sets window's default sizes and name
	sf::RenderWindow window{ sf::VideoMode{1000, 600}, "Mario", sf::Style::Titlebar | sf::Style::Close };

	Resources::loadFiles(window);
	Resources::themesongM.setLoop(true);
	Resources::themesongM.play();

	LevelManager levelManager;
	return levelManager.run(window);
}