#include "Endpoint.h"

void Endpoint::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(castle);

	// only draw after animation gottriggered
	if(animationTrigger)
		target.draw(flag);
}

void Endpoint::initializeIn(const sf::Vector2f & position, const float scale)
{
	/*ANIMATION*/
	animPos = { 0, 0 };

	/*PROPERTIES*/
	animationTrigger = false;
	gameWon = false;

	/*SCALE*/
	castle.setScale({ scale, scale });
	flag.setScale({ scale, scale });

	/*POSITIONING*/
	castle.setPosition(position);

	flag.setPosition({castle.getPosition().x - flag.getGlobalBounds().width / 2,
					  castle.getGlobalBounds().top + castle.getGlobalBounds().height - flag.getGlobalBounds().height});
	animPos = flag.getPosition(); // starting position of flag animation

	// fake bounds for more accuracy (measured with Photoshop)
	animBounds = { castle.getGlobalBounds().left + castle.getGlobalBounds().width / 22.125f,
				   castle.getGlobalBounds().top, 
				   castle.getGlobalBounds().width - castle.getGlobalBounds().width / 22.125f,
				   castle.getGlobalBounds().height };
}

void Endpoint::detection(Character & character, const float dt)
{
	if (animBounds.intersects(character.getGlobalBounds()) && !animationTrigger) {
		// play winning song
		Resources::stopAllSongs();
		Resources::stageClearM.play();

		// calculate the position flag has to animate to
		animPos = { castle.getPosition().x - flag.getGlobalBounds().width / 2, character.getPosition().y };

		// make sure its under the height of castle
		if (animPos.y < castle.getPosition().y) {
			animPos.y = castle.getPosition().y;
		}

		/* formula to calculate the percentage of score given */
		float percentage = ((castle.getGlobalBounds().height - animPos.y + castle.getGlobalBounds().top) / castle.getGlobalBounds().height);

		// add score calculated
		Score::add(int(200 * percentage));

		// disable character keys
		character.disableKeys();

		// trigger win animation
		animationTrigger = true;
	}

	if (animationTrigger) { // do animation
		// position to the gate of castle (measured with Photoshop)
		if (character.getPosition().x < castle.getGlobalBounds().left + castle.getGlobalBounds().width * 0.7344f) {
			character.walkRight(300 * dt);
		}
		else {
			// makes it look like character enters the door
			character.setVisibility(false);

			// ends game after music finishes playing
			if (Resources::stageClearM.getStatus() != sf::Music::Playing) {
				gameWon = true;
			}
		}
	}

	// flag animation
	if (!(flag.getPosition().y >= animPos.y - 2 && animPos.y + 2 >= flag.getPosition().y)) {
		float offset = -400 * dt;
		flag.move({ 0, offset });
	}
}
