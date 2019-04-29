#include "ReadWrite.h"

float ReadWrite::mapLength = WIDTH;
inOutObj ReadWrite::character1 = { {notfound, notfound} , 0 ,0 };
inOutObj ReadWrite::character2 = { {notfound, notfound} , 0 ,0 };
std::vector<inOutObj> ReadWrite::enemies;
std::vector<inOutObj> ReadWrite::healers;
std::vector<inOutObj> ReadWrite::bricks;
std::vector<inOutObj> ReadWrite::grounds;

void ReadWrite::resetVariables()
{
	character1 = { {notfound, notfound} , 0 ,0 };
	character2 = { {notfound, notfound} , 0 ,0 };
	enemies.clear();
	healers.clear();
	bricks.clear();
	grounds.clear();
}

int ReadWrite::clearInput(std::string & input)
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

void ReadWrite::readMap()
{
	std::ifstream in(Paths::getFilePath());
	std::string input;

	// used only for displaying the line error messages are found on
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
			if (input == "character1") {
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
			else if (input == "healer") {
				float xtemp, ytemp, scaletemp;

				in >> xtemp >> ytemp >> scaletemp;
				healers.push_back({ {xtemp, ytemp}, scaletemp });
			}
			else respMessage = 0;
		}
		else if (respMessage == 0) { // if response == error then warn
			std::cout << "WARNING! path: " << Paths::getFilePath() <<" line: " << iterator << " contains WRONG input." << std::endl;
			// the line is only correctly displayed here if spaces aren't messed up
		}

		iterator++;
	}
}

void ReadWrite::saveMap()
{
	std::string path = Paths::getFilePath();
	/*Erases unnecessary path extensions*/
	size_t found = path.find(".txt");
	while (found != std::string::npos) {
		path.erase(found, 4);
		found = path.find(".txt");
	}

	std::ofstream out(path + ".txt");

	out << "!! type posx posy scale" << std::endl; // these are comments for easier manual troubleshooting

	// save the length of the map
	out << "maplenght " << mapLength << std::endl;
	std::cout << "maplenght " << mapLength << std::endl;

	if (character1.pos.x != notfound && character1.pos.y != notfound) {
		out << "character1 " << character1.pos.x << " " << character1.pos.y << " " << character1.scale << std::endl;
	}
	if (character2.pos.x != notfound && character2.pos.y != notfound) {
		out << "character2 " << character2.pos.x << " " << character2.pos.y << " " << character2.scale << std::endl;
	}

	for (int i = 0; i < int(enemies.size()); i++) {
		out << "enemy " << enemies[i].pos.x << " " << enemies[i].pos.y << " " << enemies[i].scale << std::endl;
	}
	for (int i = 0; i < int(healers.size()); i++) {
		out << "healer " << healers[i].pos.x << " " << healers[i].pos.y << " " << healers[i].scale << std::endl;
	}

	out << "!! type posx posy scale width" << std::endl; // these are comments for easier manual troubleshooting

	for (int i = 0; i < int(bricks.size()); i++) {
		out << "brick " << bricks[i].pos.x << " " << bricks[i].pos.y << " " << bricks[i].scale << " " << bricks[i].size << std::endl;
	}
	for (int i = 0; i < int(grounds.size()); i++) {
		out << "ground " << grounds[i].pos.x << " " << grounds[i].pos.y << " " << grounds[i].scale << " " << grounds[i].size << std::endl;
	}
}

void ReadWrite::uploadObj(const std::vector<sf::RectangleShape>& obj, const std::vector<int>& objType)
{
	resetVariables();

	for (int i = 0; i < int(obj.size()); i++) {
		if (objType[i] == Mouse::marioID) {
			character1.pos.x = obj[i].getPosition().x;
			character1.pos.y = obj[i].getPosition().y;
			character1.scale = obj[i].getScale().x;
		} else if (objType[i] == Mouse::luigiID) {
			character2.pos.x = obj[i].getPosition().x;
			character2.pos.y = obj[i].getPosition().y;
			character2.scale = obj[i].getScale().x;
		}
		else if (objType[i] == Mouse::enemyID) {
			enemies.push_back({ { obj[i].getPosition().x, obj[i].getPosition().y }, obj[i].getScale().x });
		}
		else if (objType[i] == Mouse::healerID) {
			healers.push_back({ { obj[i].getPosition().x, obj[i].getPosition().y }, obj[i].getScale().x });
		}
		else if (objType[i] == Mouse::brickID) {
			bricks.push_back({ { obj[i].getPosition().x, obj[i].getPosition().y }, obj[i].getScale().x, int(obj[i].getSize().x / Resources::brickT.getSize().x) });
		}
		else if (objType[i] == Mouse::groundID) {
			grounds.push_back({ { obj[i].getPosition().x, obj[i].getPosition().y }, obj[i].getScale().x, int(obj[i].getSize().x / Resources::groundT.getSize().x) });
		}
	}
}
