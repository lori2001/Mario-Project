#include "Editor.h"

void Editor::loadMap()
{
	ReadWrite::readMap();
	objects.clear();
	objectsType.clear();

	lengthMark.setPosition({ ReadWrite::getMapLength().x, 0 });

	/* turns all loaded text in sprites on screen*/
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
	if (ReadWrite::getEndpoint().pos.x != notfound && ReadWrite::getEndpoint().pos.y != notfound) {
		sf::RectangleShape temp;
		temp.setTexture(&Resources::castle_smallT);
		temp.setPosition({ ReadWrite::getEndpoint().pos.x, ReadWrite::getEndpoint().pos.y });
		temp.setSize({ 177, 168 });
		temp.setTextureRect({ 0,0, 177, 168 });
		temp.setScale({ ReadWrite::getEndpoint().scale, ReadWrite::getEndpoint().scale });

		objects.push_back(temp);
		objectsType.push_back(Mouse::endpointID);
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
	for (int i = 0; i < ReadWrite::getCoinsNum(); i++) {
		sf::RectangleShape temp;
		temp.setTexture(&Resources::coinT);
		temp.setPosition({ ReadWrite::getCoin(i).pos.x, ReadWrite::getCoin(i).pos.y });
		temp.setSize({ 8, 14 });
		temp.setTextureRect({ 0,0, 8, 14 });
		temp.setScale({ ReadWrite::getCoin(i).scale, ReadWrite::getCoin(i).scale });

		objects.push_back(temp);
		objectsType.push_back(Mouse::coinID);
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
	// Leave out UI
	if (mouse.getPosition().y > 80) {

		mouse.setDrawing(true);

		if (event.type == event.MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {

			mouseLock = sf::Mouse::getPosition();

			// enable multi-ground and brick placing
			if (mouse.getSelected() == Mouse::groundID || mouse.getSelected() == Mouse::brickID) {
				canLock = true;
				viewPos = window.getView().getCenter().x;
			}

			for (unsigned i = 0; i < objects.size(); i++) {
				// spawn only once (mario, luigi and endpoint)
				if ((mouse.getSelected() == Mouse::marioID && objectsType[i] == Mouse::marioID) ||
					(mouse.getSelected() == Mouse::luigiID && objectsType[i] == Mouse::luigiID) ||
					(mouse.getSelected() == Mouse::endpointID && objectsType[i] == Mouse::endpointID)) {
					objects.erase(objects.begin() + i);
					objectsType.erase(objectsType.begin() + i);
					break;
				}
				// eraser logic
				if (mouse.getGlobalBounds().intersects(objects[i].getGlobalBounds())) {
					if (mouse.getSelected() == Mouse::eraserID) {
						// erase object
						objects.erase(objects.begin() + i);
						objectsType.erase(objectsType.begin() + i);
						
						// move map length mark back to the last furthest object
						float furthestRight = 0;
						float objTop = 0;

						for (int i = 0; i < int(objects.size()); i++) {
							float objRight = objects[i].getGlobalBounds().left + objects[i].getGlobalBounds().width;
							if (furthestRight < objRight) {
								furthestRight = objRight;
								objTop = objects[i].getGlobalBounds().top;
							}
						}

						ReadWrite::setMapLength({ furthestRight, objTop });
						lengthMark.setPosition({ ReadWrite::getMapLength().x, 0 });
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
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && canLock && objects.size() > 0) {
			sf::Mouse::setPosition({ sf::Mouse::getPosition().x, mouseLock.y }); // locks mouse in the y axis
			
			// holds the position of the object in vector that is going to be modified
			const unsigned objPos = objects.size() - 1;

			// if the view gets move while placing that adds up to the size
			const float viewOffset = (window.getView().getCenter().x - viewPos) / objects[objPos].getScale().x;
			// mouse pos relative to staring point
			const float relativeMouse = (sf::Mouse::getPosition().x - mouseLock.x) / objects[objPos].getScale().x * (WIDTH / window.getSize().x);

			// calculates the new size the ground element should have
			float newXSize = viewOffset + relativeMouse;

			// applies calculations 
			if (mouse.getSelected() == Mouse::groundID || mouse.getSelected() == Mouse::brickID) {
				if (objects[objPos].getSize().x < newXSize) {
					newXSize = float(int(newXSize / objects[objPos].getTexture()->getSize().x + 1) * objects[objPos].getTexture()->getSize().x);

					objects[objPos].setSize({ newXSize, objects[objPos].getSize().y });
					objects[objPos].setTextureRect({ 0,0,int(objects[objPos].getSize().x), int(objects[objPos].getSize().y) });
				}
			}
		}
		else {
			canLock = false;
		}

		if (event.type == event.MouseButtonReleased && mouse.getSelected() != Mouse::eraserID) {
			float objRight = objects[objects.size() - 1].getGlobalBounds().left + objects[objects.size() - 1].getGlobalBounds().width;
			float objTop = objects[objects.size() - 1].getGlobalBounds().top;

			// if the last object placed is beyond the limits of the map, move the limits
			if (objRight > ReadWrite::getMapLength().x) {
				ReadWrite::setMapLength({ objRight, objTop });
				lengthMark.setPosition({ ReadWrite::getMapLength().x, 0 });
			}
		}

		if (event.type == sf::Event::MouseWheelMoved) {
			if (event.mouseWheel.delta > 0) {
				mouse.changeScale(0.1f);
			}
			else if (event.mouseWheel.delta < 0) {
				mouse.changeScale(-0.1f);
			}
			else {
				std::cout << "WARNING: mouse wheel movement seems odd! value is:" << event.mouseWheel.delta << std::endl;
			}
		}
	}
	else {
		mouse.setDrawing(false);
	}
}

void Editor::Update(sf::RenderWindow & window, const float dt)
{
	mouse.setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
	mouse.updateObject();

	/*Nudge last placed object if needed*/
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		float objTop = objects[objects.size() - 1].getGlobalBounds().top;
		objects[objects.size() - 1].move({ 0,-25 * dt });

		// moves map's "last height" if necessary 
		if (objTop == ReadWrite::getMapLength().y) {
			objTop = objects[objects.size() - 1].getGlobalBounds().top;

			// set new position
			ReadWrite::setMapLength({ ReadWrite::getMapLength().x, objTop });
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		float objTop = objects[objects.size() - 1].getGlobalBounds().top;
		objects[objects.size() - 1].move({ 0,25 * dt });

		// moves map's "last height" if necessary 
		if (objTop == ReadWrite::getMapLength().y) {
			objTop = objects[objects.size() - 1].getGlobalBounds().top;

			// set new position
			ReadWrite::setMapLength({ ReadWrite::getMapLength().x, objTop });
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		float objRight = objects[objects.size() - 1].getGlobalBounds().left + objects[objects.size() - 1].getGlobalBounds().width;
		objects[objects.size() - 1].move({ -25 * dt, 0 });

		// moves map's length if necessary
		if (objRight == ReadWrite::getMapLength().x) {
			// recalculate objRight
			objRight = objects[objects.size() - 1].getGlobalBounds().left + objects[objects.size() - 1].getGlobalBounds().width;
			// set new position
			ReadWrite::setMapLength({ objRight, ReadWrite::getMapLength().y });
			lengthMark.setPosition({ ReadWrite::getMapLength().x, 0 });
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		float objRight = objects[objects.size() - 1].getGlobalBounds().left + objects[objects.size() - 1].getGlobalBounds().width;
		objects[objects.size() - 1].move({ 25 * dt, 0 });

		// moves map's length if necessary
		if (objRight == ReadWrite::getMapLength().x) {
			// recalculate objRight
			objRight = objects[objects.size() - 1].getGlobalBounds().left + objects[objects.size() - 1].getGlobalBounds().width;
			// set new position
			ReadWrite::setMapLength({ objRight, ReadWrite::getMapLength().y });
			lengthMark.setPosition({ ReadWrite::getMapLength().x, 0 });
		}
	}

	/*Lock mouse on Y axis of the last object*/
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && objects.size() > 0) {
		sf::Mouse::setPosition({ sf::Mouse::getPosition().x, mouseLock.y }); // locks mouse in the y axis
	}
	/*Lock mouse on X axis of the last object*/
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && objects.size() > 0) {
		sf::Mouse::setPosition({ mouseLock.x, sf::Mouse::getPosition().y }); // locks mouse in the y axis
	}

	groundMark.setSize({ ReadWrite::getMapLength().x, 2});
}

void Editor::Compose(sf::RenderWindow & window)
{
	window.draw(lengthMark);
	window.draw(groundMark);

	for (unsigned i = 0; i < objects.size(); i++) {
		window.draw(objects[i]);
	}

	if (mouse.getDrawing()) {
		window.draw(mouse);
	}
}
