#pragma once
#include "SFML/Graphics.hpp"
#include "Resources.h"

class Score : public sf::Text{
private:
	static sf::String basestr;
	static int totalScore;
	static int score;
public:

	Score() {
		Text::setFont(Resources::super_marioF);
		Text::setCharacterSize(35);
		Text::setString(basestr + std::to_string(score));
	}

	// sets total score to 0
	static void resetTotal();
	// add current score to total
	static void addScoreToTotal();
	// get total score (for entire world)
	static int getTotal();
	
	static void add(const int param);
	static void subs(const int param);
	static void equal(const int param);

	void updateString();

	/* Ofh...
	Score operator = (const int param);
	Score operator -= (const int param);
	Score operator += (const int param);*/
};