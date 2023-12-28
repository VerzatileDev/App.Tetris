#include "SFML/Graphics.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode::VideoMode(320, 480), "Tetris");

	while (window.isOpen())
	{
		sf::Texture t;
		t.loadFromFile("Textures/tiles.png");
		sf::Sprite s(t);

		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Black);

		window.draw(s);
		window.display();
	}
	return 0;
}