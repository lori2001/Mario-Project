#include "Paths.h"

std::string Paths::gamePath;
std::string Paths::filePath;
nfdchar_t* Paths::path = NULL;
nfdresult_t Paths::dialog;

bool Paths::chooseGamePath()
{
	std::cout << "Please choose the location of the Mario game folder!" << std::endl;

	path = NULL;
	dialog = NFD_PickFolder(NULL, &path);

	if (dialog == NFD_OKAY) {
		gamePath = path;
		free(path);
	}
	else if (dialog == NFD_CANCEL) {
		return false;
	}
	else {
		std::cout << "Error: " << NFD_GetError() << std::endl;
	}

	return true;
}
bool Paths::saveFilePath()
{
	path = NULL;
	dialog = NFD_SaveDialog("map", NULL, &path);

	if (dialog == NFD_OKAY)
	{
		filePath = path;
		free(path);
	}
	else if (dialog == NFD_CANCEL)
	{
		return false;
	}
	else
	{
		std::cout << "Error: " << NFD_GetError();
	}

	return true;
}
bool Paths::openFilePath()
{

	path = NULL;
	dialog = NFD_OpenDialog("map,unit,json", NULL, &path);

	if (dialog == NFD_OKAY)
	{
		filePath = path;
		free(path);
	}
	else if (dialog == NFD_CANCEL)
	{
		return false;
	}
	else
	{
		std::cout << "Error: " << NFD_GetError();
	}

	return true;
}