#pragma once
#include "SFML/Graphics.hpp"
#include "Resources.h"

class Score : public sf::Text {
private:
	sf::String basestr = "Score: ";

	static int totalScore;
	static int score;
public:
	Score() {
		Text::setFont(Resources::super_marioF);
		Text::setCharacterSize(35);
		Text::setString(basestr + std::to_string(score));
	}

	// sets total score to param
	static void setTotal(const int newtotal) { totalScore = newtotal; }
	// add given number to total score count
	static void changeTotal(int offset) { totalScore += offset; }
	// get total score (for entire world)
	static int getTotal() { return totalScore; }

	// sets current score to param
	static void setScore(const int newscore) { score = newscore; }
	// changes current score (adds given number to score)
	static void changeScore(const int offset) { score += offset; }
	// returns score as integer
	static int getScore() { return score; }

	// updates string based on current score
	void updateString() { Text::setString(basestr + std::to_string(score)); }

	// sets text before score
	void setBaseStr(sf::String newbase) { basestr = newbase; updateString(); }

};
