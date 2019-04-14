#include <SFML/Graphics.hpp>
#include "Editor.h"
// #include "../vendor/json-develop/nlohmann/json.hpp"

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

	sf::RenderWindow window{ sf::VideoMode{1000, 600 }, "Mario Map Editor" }; // creates and sets window's default sizes and name

	//Resources resources;
	//resources.loadFiles(window);

	Editor editor;
	return editor.run(window);
}