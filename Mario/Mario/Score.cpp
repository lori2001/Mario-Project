#include "Score.h"

sf::String Score::basestr = "Score: ";
int Score::totalScore = 0;
int Score::score = 0;

void Score::resetTotal()
{
	totalScore = 0;
}

void Score::addScoreToTotal()
{
	totalScore += score;
}

int Score::getTotal()
{
	return totalScore;
}

void Score::add(const int param)
{
	score += param;
}

void Score::subs(const int param)
{
	score -= param;
}

void Score::equal(const int param)
{
	score = param;
}

void Score::updateString()
{
	Text::setString(basestr + std::to_string(score));
}
