#include "Maps.h"

std::vector<std::string> Maps::maps;
sf::Vector2f Maps::character1 = { notfound, notfound };
sf::Vector2f Maps::character2 = { notfound, notfound };
std::vector<sf::Vector2f> Maps::enemies;
std::vector<sf::Vector2f> Maps::healers;
std::vector<sf::Vector3f> Maps::bricks;
std::vector<sf::Vector3f> Maps::grounds;

void Maps::clearVariables()
{
	character1 = { notfound, notfound };
	character2 = { notfound, notfound };
	enemies.clear();
	healers.clear();
	bricks.clear();
	grounds.clear();
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

		if (input != " " && !onlyspaces) // check against ignore conditions
		{
			maps.push_back(input);
		}
		else if(!comment) { // warn in debugger console for ignored lines (in case its not a comment)
			std::cout << "WARNING! assets/maps/list.txt line: " << iterator << " could not be read." << std::endl;
		}

		iterator++;
	}
}

void Maps::readMap(int mapnumber)
{
	std::ifstream in("assets/maps/" + maps[mapnumber]);
	std::string input;

	clearVariables();

	/* organizes information in dedicated vectors */
	while (in >> input) {
		if (input == "character1") {
			in >> character1.x >> character1.y;
		}
		else if(input == "character2") {
			in >> character2.x >> character2.y;
		}
		else if (input == "enemy") {
			float xtemp, ytemp;
			in >> xtemp >> ytemp;
			enemies.push_back({ xtemp, ytemp });
		}
		else if (input == "brick") {
			float xtemp, ytemp, size;
			in >> xtemp >> ytemp >> size;
			bricks.push_back({ xtemp, ytemp, size });
		}
		else if (input == "ground") {
			float xtemp, ytemp, size;
			in >> xtemp >> ytemp >> size;
			grounds.push_back({ xtemp, ytemp, size });
		}
		else if (input == "healer") {
			float xtemp, ytemp;
			in >> xtemp >> ytemp;
			healers.push_back({ xtemp, ytemp });
		}
	}
}
