#include "Editor.h"

void Editor::loadMap()
{
	ReadWrite::readMap();
	objects.clear();

	if (ReadWrite::getCharacter1().pos.x != notfound && ReadWrite::getCharacter1().pos.y != notfound) {
		sf::RectangleShape temp;
		temp.setTexture(&Resources::mario_smallT);
		temp.setPosition({ ReadWrite::getCharacter1().pos.x, ReadWrite::getCharacter1().pos.y });
		temp.setSize({ 13, 16 });
		temp.setTextureRect({ 0,0, 13, 16 });
		temp.setScale({ ReadWrite::getCharacter1().scale, ReadWrite::getCharacter1().scale });

		objects.push_back(temp);
		objectsType.push_back(Mouse::marioID);
	}
	if (ReadWrite::getCharacter2().pos.x != notfound && ReadWrite::getCharacter2().pos.y != notfound) {
		sf::RectangleShape temp;
		temp.setTexture(&Resources::luigi_smallT);
		temp.setPosition({ ReadWrite::getCharacter2().pos.x, ReadWrite::getCharacter2().pos.y });
		temp.setSize({ 13, 16 });
		temp.setTextureRect({ 0,0, 13, 16 });
		temp.setScale({ ReadWrite::getCharacter2().scale, ReadWrite::getCharacter2().scale });

		objects.push_back(temp);
		objectsType.push_back(Mouse::luigiID);
	}

	for (int i = 0; i < ReadWrite::getEnemiesNum(); i++) {
		sf::RectangleShape temp;
		temp.setTexture(&Resources::enemy_mushT);
		temp.setPosition({ ReadWrite::getEnemy(i).pos.x, ReadWrite::getEnemy(i).pos.y });
		temp.setSize({ 16, 16 });
		temp.setTextureRect({ 0,0, 16, 16 });
		temp.setScale({ ReadWrite::getEnemy(i).scale, ReadWrite::getEnemy(i).scale });

		objects.push_back(temp);
		objectsType.push_back(Mouse::enemyID);
	}
	for (int i = 0; i < ReadWrite::getHealersNum(); i++) {
		sf::RectangleShape temp;
		temp.setTexture(&Resources::good_mushT);
		temp.setPosition({ ReadWrite::getHealer(i).pos.x, ReadWrite::getHealer(i).pos.y });
		temp.setSize({ 16, 16 });
		temp.setTextureRect({ 0,0, 16, 16 });
		temp.setScale({ ReadWrite::getHealer(i).scale, ReadWrite::getHealer(i).scale });

		objects.push_back(temp);
		objectsType.push_back(Mouse::healerID);
	}
	for (int i = 0; i < ReadWrite::getBricksNum(); i++) {
		sf::RectangleShape temp;
		temp.setTexture(&Resources::brickT);
		temp.setPosition({ ReadWrite::getBrick(i).pos.x, ReadWrite::getBrick(i).pos.y });
		temp.setScale({ ReadWrite::getBrick(i).scale, ReadWrite::getBrick(i).scale });
		temp.setSize({ float(ReadWrite::getBrick(i).size * Resources::brickT.getSize().x), float(Resources::brickT.getSize().y) });
		temp.setTextureRect({ 0,0, int(ReadWrite::getBrick(i).size * Resources::brickT.getSize().x), int(Resources::brickT.getSize().y) });

		objects.push_back(temp);
		objectsType.push_back(Mouse::brickID);
	}
	for (int i = 0; i < ReadWrite::getGroundsNum(); i++) {
		sf::RectangleShape temp;
		temp.setTexture(&Resources::groundT);
		temp.setPosition({ ReadWrite::getGround(i).pos.x, ReadWrite::getGround(i).pos.y });
		temp.setScale({ ReadWrite::getGround(i).scale, ReadWrite::getGround(i).scale });
		temp.setSize({ float(ReadWrite::getGround(i).size * Resources::groundT.getSize().x), float(Resources::groundT.getSize().y) });
		temp.setTextureRect({ 0,0, int(ReadWrite::getGround(i).size * Resources::groundT.getSize().x), int(Resources::groundT.getSize().y) });

		objects.push_back(temp);
		objectsType.push_back(Mouse::groundID);
	}
}

void Editor::saveMap()
{
	ReadWrite::uploadObj(objects, objectsType);
	ReadWrite::saveMap();
}

void Editor::handleEvents(const sf::RenderWindow & window, const sf::Event & event)
{
	mouse.setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));

	if (mouse.getPosition().y > 80) { // Eliminate UI from calculations
		if (event.type == event.MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {

			// enable multi-ground and brick placing
			if (mouse.getSelected() == Mouse::groundID || mouse.getSelected() == Mouse::brickID) {
				canLock = true;
				mouseLock = sf::Mouse::getPosition();
			}

			for (unsigned i = 0; i < objects.size(); i++) {
				// spawn only once (mario and luigi)
				if ((mouse.getSelected() == Mouse::marioID && objectsType[i] == Mouse::marioID) ||
					(mouse.getSelected() == Mouse::luigiID && objectsType[i] == Mouse::luigiID)) {
					objects.erase(objects.begin() + i);
					objectsType.erase(objectsType.begin() + i);
					break;
				}
				// eraser logic
				if (mouse.getGlobalBounds().intersects(objects[i].getGlobalBounds())) {
					if (mouse.getSelected() == Mouse::eraserID) {
						objects.erase(objects.begin() + i);
						objectsType.erase(objectsType.begin() + i);
					}
				}
			}

			// spawn everything except the eraser
			if(mouse.getSelected() != Mouse::eraserID) {
				objects.push_back(mouse);
				objectsType.push_back(mouse.getSelected());
			}
		}

		// multi ground and brick placing when holding mouse button
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && canLock) {
			sf::Mouse::setPosition({ sf::Mouse::getPosition().x, mouseLock.y });

			float newXSize = float(sf::Mouse::getPosition().x - mouseLock.x);
			unsigned objPos = objects.size() - 1;

			if (mouse.getSelected() == Mouse::groundID) {
				if (objects[objPos].getSize().x < newXSize) {

					newXSize = float(int(newXSize / Resources::groundT.getSize().x + 1) * Resources::groundT.getSize().x);

					objects[objPos].setSize({ newXSize, objects[objPos].getSize().y });
					objects[objPos].setTextureRect({ 0,0,int(objects[objPos].getSize().x), int(objects[objPos].getSize().y) });
				}
				else if (mouse.getPosition().x < objects[objPos].getPosition().x) {
					sf::Mouse::setPosition(mouseLock);
				}
			}
			else if (mouse.getSelected() == Mouse::brickID) {
				if (objects[objPos].getSize().x < newXSize) {

					newXSize = float(int(newXSize / Resources::brickT.getSize().x + 1) * Resources::brickT.getSize().x);

					objects[objPos].setSize({ newXSize, objects[objPos].getSize().y });
					objects[objPos].setTextureRect({ 0,0,int(objects[objPos].getSize().x), int(objects[objPos].getSize().y) });
				}
				else if (mouse.getPosition().x < objects[objPos].getPosition().x) {
					sf::Mouse::setPosition(mouseLock);
				}
			}
		}
		else {
			canLock = false;
		}
	}
}

void Editor::Update(sf::RenderWindow & window)
{
	mouse.updateObject();
}

void Editor::Compose(sf::RenderWindow & window)
{
	for (unsigned i = 0; i < objects.size(); i++) {
		window.draw(objects[i]);
	}
	window.draw(mouse);
}
