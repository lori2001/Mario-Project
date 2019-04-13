#pragma once
#include "SFML/Graphics.hpp"
#include "Resources.h"

class Score : public sf::Text{
private:
	static sf::String basestr;
	static int score;
public:

	Score() {
		Text::setFont(Resources::super_marioF);
		Text::setCharacterSize(35);
		Text::setString(basestr + std::to_string(score));
	}
	
	static void add(const int param);
	static void subs(const int param);
	static void equal(const int param);

	void updateString();

	/* Ofh...
	Score operator = (const int param);
	Score operator -= (const int param);
	Score operator += (const int param);*/
};