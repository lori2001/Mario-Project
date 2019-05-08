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

	std::vector<int> usedGrounds;
	int groundsNum = 0; // number of ground entities(one object contains more entities)
	float groundSurface = 0; // the total surface area of the grounds

	// count how many ground objects there are
	for (int i = 0; i < int(grounds.size()); i++) {
		if (grounds[i].getGlobalBounds(0).top > HEIGHT - (HEIGHT / 8)) {
			usedGrounds.push_back(i);
			for (int rown = 0; rown < grounds[i].getRowSize(); rown++) {
				groundsNum++;
				groundSurface += grounds[i].getGlobalBounds(rown).width;
			}
		}
	}

	int scalar = int(groundSurface / WIDTH); // the scale at which things have to be generated
	if (scalar <= 0) scalar = 1;

	int HoTNum = rand() % (2 * scalar) + (4 * scalar); // number of hills or trees
	int cloudNum = rand() % (2 * scalar) + (4 * scalar); // number of clouds
	int bushNum = rand() % (2 * scalar) + (5 * scalar); // number of bushes

	std::random_device rand_dev;
	generator = std::mt19937(rand_dev());

	// reseed uniform distribution for clouds
	distribution = std::uniform_int_distribution<int>(10, int(Maps::getMapLength()));
	std::uniform_int_distribution<int> Ydist{ 10, int(Maps::getMapLength()) };

	// clouds
	for (int i = 0; i < cloudNum; i++) {

		float posX = float(distribution(generator)); // the index of ground it will be placed on
		float posY = float(Ydist(generator) % int(HEIGHT - 450) + 50); // the index of ground it will be placed on

		if (rand() % 2)
			objects.push_back(newObject(4));
		else
			objects.push_back(newObject(5));

		objects[objects.size() - 1].setPosition({ posX, posY });
	}

	// reseed uniform distribution for ground-based objects
	distribution = std::uniform_int_distribution<int>(1, groundsNum);

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

		int groundCount = -1; // don't try this at home :P
		for (int gi = 0; gi < int(usedGrounds.size()); gi++) { // go through each ground object
			for (int rown = 0; rown < grounds[usedGrounds[gi]].getRowSize(); rown++) {
				groundCount++;
				if (groundCount == posXGround) {
					if(hills) objects.push_back(newObject(0));
					else objects.push_back(newObject(2));

					const float posX = grounds[usedGrounds[gi]].getGlobalBounds(rown).left;
					const float posY = grounds[usedGrounds[gi]].getGlobalBounds(rown).top - objects[objects.size() - 1].getGlobalBounds().height;
					objects[objects.size() - 1].setPosition({ posX, posY });

					if (objects[objects.size() - 1].getGlobalBounds().left + objects[objects.size() - 1].getGlobalBounds().width >
					grounds[usedGrounds[gi]].getGlobalBounds(grounds[usedGrounds[gi]].getRowSize() - 1).left
					+ grounds[usedGrounds[gi]].getGlobalBounds(grounds[usedGrounds[gi]].getRowSize() - 1).width) {
						objects.erase(objects.begin() + objects.size() - 1); // erase misplaced scenery ( im lazy to fix it :D
					}

					break;
				}
			}
			if (groundCount == posXGround) break;
		}
	}
	
	// small hills or trees
	for (int i = HoTType2; i < HoTNum; i++) {
		int posXGround = distribution(generator); // the index of ground it will be placed on

		int groundCount = -1; // don't try this at home :P
		for (int gi = 0; gi < int(usedGrounds.size()); gi++) { // go through each ground object
			for (int rown = 0; rown < grounds[usedGrounds[gi]].getRowSize(); rown++) {
				groundCount++;
				if (groundCount == posXGround) {
					if (hills) objects.push_back(newObject(1));
					else objects.push_back(newObject(3));

					const float posX = grounds[usedGrounds[gi]].getGlobalBounds(rown).left;
					const float posY = grounds[usedGrounds[gi]].getGlobalBounds(rown).top - objects[objects.size() - 1].getGlobalBounds().height;
					objects[objects.size() - 1].setPosition({ posX, posY });

					if (objects[objects.size() - 1].getGlobalBounds().left + objects[objects.size() - 1].getGlobalBounds().width >
					grounds[usedGrounds[gi]].getGlobalBounds(grounds[usedGrounds[gi]].getRowSize() - 1).left
					+ grounds[usedGrounds[gi]].getGlobalBounds(grounds[usedGrounds[gi]].getRowSize() - 1).width) {
						objects.erase(objects.begin() + objects.size() - 1); // erase misplaced scenery ( im lazy to fix it :D
					}

					break;
				}
			}
			if (groundCount == posXGround) break;
		}
	}

	// big bushes
	for (int i = 0; i < bushType1; i++) {
		int posXGround = distribution(generator); // the index of ground it will be placed on

		int groundCount = -1; // don't try this at home :P
		for (int gi = 0; gi < int(usedGrounds.size()); gi++) { // go through each ground object
			for (int rown = 0; rown < grounds[usedGrounds[gi]].getRowSize(); rown++) {
				groundCount++;
				if (groundCount == posXGround) {
					objects.push_back(newObject(6));

					const float posX = grounds[usedGrounds[gi]].getGlobalBounds(rown).left;
					const float posY = grounds[usedGrounds[gi]].getGlobalBounds(rown).top - objects[objects.size() - 1].getGlobalBounds().height;
					objects[objects.size() - 1].setPosition({ posX, posY });

					if (objects[objects.size() - 1].getGlobalBounds().left + objects[objects.size() - 1].getGlobalBounds().width >
						grounds[usedGrounds[gi]].getGlobalBounds(grounds[usedGrounds[gi]].getRowSize() - 1).left
						+ grounds[usedGrounds[gi]].getGlobalBounds(grounds[usedGrounds[gi]].getRowSize() - 1).width) {
						objects.erase(objects.begin() + objects.size() - 1); // erase misplaced scenery ( im lazy to fix it :D
					}

					break;
				}
			}
			if (groundCount == posXGround) break;
		}
	}

	// small bushes
	for (int i = bushType1; i < bushNum; i++) {
		int posXGround = distribution(generator); // the index of ground it will be placed on

		int groundCount = -1; // don't try this at home :P
		for (int gi = 0; gi < int(usedGrounds.size()); gi++) { // go through each ground object
			for (int rown = 0; rown < grounds[usedGrounds[gi]].getRowSize(); rown++) {
				groundCount++;
				if (groundCount == posXGround) {
					objects.push_back(newObject(7));

					const float posX = grounds[usedGrounds[gi]].getGlobalBounds(rown).left;
					const float posY = grounds[usedGrounds[gi]].getGlobalBounds(rown).top - objects[objects.size() - 1].getGlobalBounds().height;
					objects[objects.size() - 1].setPosition({ posX, posY });

					if (objects[objects.size() - 1].getGlobalBounds().left + objects[objects.size() - 1].getGlobalBounds().width >
						grounds[usedGrounds[gi]].getGlobalBounds(grounds[usedGrounds[gi]].getRowSize() - 1).left
						+ grounds[usedGrounds[gi]].getGlobalBounds(grounds[usedGrounds[gi]].getRowSize() - 1).width) {
						objects.erase(objects.begin() + objects.size() - 1); // erase misplaced scenery ( im lazy to fix it :D
					}

					break;
				}
			}
			if (groundCount == posXGround) break;
		}
	}
}

sf::RectangleShape Scenery::newObject(int type)
{
	float addScale = float(rand() % 15) / 10; // additional scale from 0.0f to 1.5f inclusive

	sf::RectangleShape temp;
	temp.setTexture(&Resources::sceneryT);
	temp.setScale({ 4.0f + addScale, 4.0f + addScale });
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
