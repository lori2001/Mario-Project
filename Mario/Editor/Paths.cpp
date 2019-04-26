#include "Paths.h"

std::string Paths::gamePath;
std::string Paths::filePath;
nfdchar_t* Paths::path = NULL;
nfdresult_t Paths::dialog;

bool Paths::chooseGamePath()
{
	std::cout << "Game not found! Please choose mario game folder location manually!" << std::endl;

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

	gamePath.append("\\");

	return true;
}
bool Paths::saveFilePath()
{
	path = NULL;
	dialog = NFD_SaveDialog("txt", NULL, &path);

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
	dialog = NFD_OpenDialog("txt", NULL, &path);

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
