#include "Maps.h"

float Maps::mapLength;
std::vector<std::string> Maps::maps;
inputObject Maps::character1 = { {notfound, notfound} , 0 ,0 };
inputObject Maps::character2 = { {notfound, notfound} , 0 ,0 };
std::vector<inputObject> Maps::enemies;
std::vector<inputObject> Maps::healers;
std::vector<inputObject> Maps::bricks;
std::vector<inputObject> Maps::grounds;

void Maps::resetVariables()
{
	mapLength = 0;
	character1 = { {notfound, notfound} , 0 ,0 };
	character2 = { {notfound, notfound} , 0 ,0 };
	enemies.clear();
	healers.clear();
	bricks.clear();
	grounds.clear();
}

int Maps::clearInput(std::string & input)
{
	bool onlyspaces = true;

	size_t commentpos = input.find("!!"); // these are the caracters that mean comment
	bool comment = false;

	// find and erase comments from any line
	if (commentpos != std::string::npos) {
		input.erase(commentpos, input.length());
		comment = true;
	}

	for (std::string::const_iterator i = input.begin(); i != input.end(); ++i) // checks for potential empty lines and ignores them
	{
		if (onlyspaces && *i != ' ' && *i != '\t')
		{
			onlyspaces = false;
		}
	}

	if (input != " " && !onlyspaces) {
		return 1;
	}
	else if (!comment) {
		return 0;
	}
	else {
		return 2;
	}
}

void Maps::readList()
{
	std::ifstream in("assets/maps/list.txt");
	std::string input;
	int iterator = 1;

	if (!in) //if reading fails
	{
		std::cout << "ERROR: assets/maps/list.txt does not exist.";
		assert(false);
	}
	else while (std::getline(in, input))
	{
		// clear input and check against ignore conditions
		int respMessage = clearInput(input);

		if (respMessage == 1) // if response == good proceed
		{
			maps.push_back(input);
		}
		else if(respMessage == 0) { // if response == error, warn
			std::cout << "WARNING! assets/maps/list.txt line: " << iterator << " could not be read." << std::endl;
		}

		iterator++;
	}
}

void Maps::readMap(int mapnumber)
{
	std::ifstream in("assets/maps/" + maps[mapnumber]);
	std::string input;
	int iterator = 1;

	resetVariables();

	/* organizes information in dedicated vectors */
	while (in >> input) {

		// clear input and check against ignore conditions
		int respMessage = clearInput(input);

		if (respMessage == 1) // if response == good proceed
		{
			if (input == "maplength") {
				in >> mapLength;
			}
			else if (input == "character1") {
				in >> character1.pos.x >> character1.pos.y >> character1.scale;
			}
			else if (input == "character2") {
				in >> character2.pos.x >> character2.pos.y >> character2.scale;
			}
			else if (input == "enemy") {
				float xtemp, ytemp, scaletemp;

				in >> xtemp >> ytemp >> scaletemp;
				enemies.push_back({ {xtemp, ytemp}, scaletemp });
			}
			else if (input == "brick") {
				float xtemp, ytemp, scaletemp;
				int size;

				in >> xtemp >> ytemp >> scaletemp >> size;
				bricks.push_back({ {xtemp, ytemp}, scaletemp , size });
			}
			else if (input == "ground") {
				float xtemp, ytemp, scaletemp;
				int size;

				in >> xtemp >> ytemp >> scaletemp >> size;
				grounds.push_back({ {xtemp, ytemp}, scaletemp , size });
			}
			else if (input == "healer") { /* this might change in the future */
				float xtemp, ytemp, scaletemp;

				in >> xtemp >> ytemp >> scaletemp;
				healers.push_back({ {xtemp, ytemp}, scaletemp });
			}
			else respMessage = 0;
		}
		else if (respMessage == 0) { // if response == error, warn
			std::cout << "WARNING! path: assets/maps/" + maps[mapnumber] << " line: " << iterator << " contains WRONG input." << std::endl;
			// iterator expects spaces wherever the editor does
		}


		iterator++;
	}
}
