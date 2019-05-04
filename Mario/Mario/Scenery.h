#pragma once
#include <vector>
#include <random>
#include "SFML/Graphics.hpp"
#include "Resources.h"
#include "Maps.h"
#include "Ground.h"

class Scenery : public sf::Drawable {
public:

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	// generates scenery on given view position
	void generate(const std::vector<Ground>& grounds);
private:
	std::vector<sf::RectangleShape> objects;

	/*random number generator in uniform distribution*/
	std::random_device                  rand_dev;
	std::mt19937                        generator;
	std::uniform_int_distribution<int>  distribution;

	// generates a new object with param type
	sf::RectangleShape newObject(int type);

	/*Sizes of each sprite inside the scenery dedicated file*/
	sf::Vector2i sprites[8] = { {80, 35}, // big hill
								{48, 19}, // small hill
								{16, 46}, // big tree
								{14, 30}, // small tree
								{64, 24}, // big cloud
								{32, 24}, // small cloud
								{64, 16}, // big bush
								{32, 16} }; // small bush
	sf::Vector2i animationPlace(const unsigned &index); // calculates the place of a texture in file
};
