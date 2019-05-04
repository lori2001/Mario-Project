#include "Scenery.h"

void Scenery::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (int i = 0; i < int(objects.size()); i++) {
		target.draw(objects[i]);
	}
}

void Scenery::generate(const std::vector<Ground>& grounds)
{
	objects.clear(); // clear all previous generations
	srand(unsigned(time(NULL))); // reseed random number

	int scalar = int(Maps::getMapLength() / WIDTH); // the scale at which things have to be generated
	if (scalar <= 0) scalar = 1;

	int HoTNum = rand() % (2 * scalar) + (3 * scalar); // number of hills or trees
	int cloudNum = rand() % (2 * scalar) + (4 * scalar); // number of clouds
	int bushNum = rand() % (2 * scalar) + (4 * scalar); // number of bushes

	std::vector<int> usedGrounds;
	int groundsNum = 0;

	// count how many ground objects there are
	for (int i = 0; i < int(grounds.size()); i++) {
		if (grounds[i].getGlobalBounds(0).top > HEIGHT - (HEIGHT / 8)) {
			usedGrounds.push_back(i);
			for (int rown = 0; rown < grounds[i].getRowSize(); rown++) {
				groundsNum++;
			}
		}
	}

	generator = std::mt19937(rand_dev());

	// reseed uniform distribution for clouds
	distribution = std::uniform_int_distribution<int>(10, int(Maps::getMapLength()));

	// clouds
	for (int i = 0; i < cloudNum; i++) {

		float posX = float(distribution(generator)); // the index of ground it will be placed on
		float posY = float(rand() % int(HEIGHT - 450) + 50); // the index of ground it will be placed on

		if (rand() % 2)
			objects.push_back(newObject(4));
		else
			objects.push_back(newObject(5));

		objects[objects.size() - 1].setPosition({ posX, posY });
	}

	// reseed uniform distribution for ground-based objects
	distribution = std::uniform_int_distribution<int>(1, groundsNum - 14);

	// hill or tree type 1 and 2
	int HoTType1 = HoTNum - (rand() % HoTNum);
	int HoTType2 = HoTNum - HoTType1;
	// bush type 1 and 2
	int bushType1 = bushNum - (rand() % bushNum);
	int bushType2 = bushNum - bushType1;

	bool hills = bool(rand() % 2 == 0); // reandomize whether hills or trees will be used
	// big hills or trees
	for (int i = 0; i < HoTType1; i++) {

		int posXGround = distribution(generator); // the index of ground it will be placed on

		int groundCount = 0;
		for (int gi = 0; gi < int(usedGrounds.size()); gi++) { // go through each ground object
			for (int rown = 0; rown < grounds[usedGrounds[gi]].getRowSize(); rown++) {
				if (groundCount == posXGround) {
					if(hills) objects.push_back(newObject(0));
					else objects.push_back(newObject(2));

					const float posX = grounds[usedGrounds[gi]].getGlobalBounds(rown).left;
					const float posY = grounds[usedGrounds[gi]].getGlobalBounds(rown).top - objects[objects.size() - 1].getGlobalBounds().height;
					objects[objects.size() - 1].setPosition({ posX, posY });

					break;
				}
				groundCount++;
			}
		}
	}
	// small hills or trees
	for (int i = HoTType2; i < HoTNum; i++) {

		int posXGround = distribution(generator); // the index of ground it will be placed on

		int groundCount = 0;
		for (int gi = 0; gi < int(usedGrounds.size()); gi++) { // go through each ground object
			for (int rown = 0; rown < grounds[usedGrounds[gi]].getRowSize(); rown++) {
				if (groundCount == posXGround) {
					if (hills) objects.push_back(newObject(1));
					else objects.push_back(newObject(3));

					const float posX = grounds[usedGrounds[gi]].getGlobalBounds(rown).left;
					const float posY = grounds[usedGrounds[gi]].getGlobalBounds(rown).top - objects[objects.size() - 1].getGlobalBounds().height;
					objects[objects.size() - 1].setPosition({ posX, posY });

					break;
				}
				groundCount++;
			}
		}
	}

	// big bushes
	for (int i = 0; i < bushType1; i++) {

		int posXGround = distribution(generator); // the index of ground it will be placed on

		int groundCount = 0;
		for (int gi = 0; gi < int(usedGrounds.size()); gi++) { // go through each ground object
			for (int rown = 0; rown < grounds[usedGrounds[gi]].getRowSize(); rown++) {
				if (groundCount == posXGround) {
					objects.push_back(newObject(6));

					const float posX = grounds[usedGrounds[gi]].getGlobalBounds(rown).left;
					const float posY = grounds[usedGrounds[gi]].getGlobalBounds(rown).top - objects[objects.size() - 1].getGlobalBounds().height;
					objects[objects.size() - 1].setPosition({ posX, posY });

					break;
				}
				groundCount++;
			}
		}
	}
	// small bushes
	for (int i = bushType1; i < bushNum; i++) {

		int posXGround = distribution(generator); // the index of ground it will be placed on

		int groundCount = 0;
		for (int gi = 0; gi < int(usedGrounds.size()); gi++) { // go through each ground object
			for (int rown = 0; rown < grounds[usedGrounds[gi]].getRowSize(); rown++) {
				if (groundCount == posXGround) {
					objects.push_back(newObject(7));

					const float posX = grounds[usedGrounds[gi]].getGlobalBounds(rown).left;
					const float posY = grounds[usedGrounds[gi]].getGlobalBounds(rown).top - objects[objects.size() - 1].getGlobalBounds().height;
					objects[objects.size() - 1].setPosition({ posX, posY });

					break;
				}
				groundCount++;
			}
		}
	}
}

sf::RectangleShape Scenery::newObject(int type)
{
	sf::RectangleShape temp;
	temp.setTexture(&Resources::sceneryT);
	temp.setScale({ 5.0f, 5.0f });
	temp.setSize(sf::Vector2f{ sprites[type] });
	temp.setTextureRect({ animationPlace(type).x, 0, sprites[type].x, sprites[type].y });

	return temp;
}

sf::Vector2i Scenery::animationPlace(const unsigned & index)
{
	sf::Vector2i temp = { 0,0 };

	for (unsigned i = 0; i < index; i++) {
		temp.x += sprites[i].x;
	}

	return temp;
}
