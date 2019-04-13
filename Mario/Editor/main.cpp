#include <SFML/Graphics.hpp>
#include "../vendor/json-develop/nlohmann/json.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1000, 600), "Mario Map Editor");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.display();
	}

	return 0;
}