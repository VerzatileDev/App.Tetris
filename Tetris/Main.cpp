#include "SFML/Graphics.hpp"
#include <time.h>

const int M = 20;
const int N = 10;

int field[M][N] = { 0 };

struct Point { int x, y; } a[4], b[4];

int figures[7][4] =
{
	1,3,5,7, // I
	2,4,5,7, // Z
	3,5,4,6, // S
	3,5,4,7, // T
	2,3,5,7, // L
	3,5,7,6, // J
	2,3,4,5, // O
};


int main()
{
	sf::RenderWindow window(sf::VideoMode::VideoMode(320, 480), "Tetris");

	sf::Texture t;
	t.loadFromFile("Textures/tiles.png");
	sf::Sprite s(t);
	s.setTextureRect(sf::IntRect(0, 0, 18, 18));

	int dx = 0; bool rotate = 0; int colorNum = 1;
	float timer = 0, delay = 0.3;

	sf::Clock clock;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed)
				if (event.key.code == sf::Keyboard::Up) rotate = true;
				else if (event.key.code == sf::Keyboard::Left) dx = -1;
				else if (event.key.code == sf::Keyboard::Right) dx = 1;
		}

		// <- Move -> //
		for (int i = 0; i < 4; i++)
		{
			a[i].x += dx;
		}

		// Rotate //
		if (rotate)
		{
			Point p = a[1]; //center of rotation
			for (int i = 0; i < 4; i++)
			{
				int x = a[i].y - p.y;
				int y = a[i].x - p.x;
				a[i].x = p.x - x;
				a[i].y = p.y + y;
			}
		}

		// Tick //
		if (timer > delay)
		{
			for (int i = 0; i < 4; i++)
			{
				a[i].y += 1;
			}
			timer = 0;
		}

		int n = 3; // or any other figure index you want
		if (a[0].x == 0)
		for (int i = 0; i < 4; i++)
		{
			a[i].x = figures[n][i] % 2;
			a[i].y = figures[n][i] / 2;
		}

		dx = 0; rotate = 0; 

		window.clear(sf::Color::Black);
		for (int i = 0; i < 4; i++)
		{
			s.setPosition(a[i].x * 18, a[i].y * 18);
			window.draw(s);
			
		}
		window.display();
	}
	return 0;
}