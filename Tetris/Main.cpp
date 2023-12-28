#include "SFML/Graphics.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode::VideoMode(320, 480), "Tetris");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Black);


		window.display();
	}
	return 0;
}