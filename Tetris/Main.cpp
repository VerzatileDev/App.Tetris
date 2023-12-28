#include "SFML/Graphics.hpp"
#include <time.h>

const int M = 20;
const int N = 10;

int field[M][N] = { 0 };

struct Point
{
    int x, y;
} a[4], b[4];

int figures[7][4] =
{
    1, 3, 5, 7, // I
    2, 4, 5, 7, // Z
    3, 5, 4, 6, // S
    3, 5, 4, 7, // T
    2, 3, 5, 7, // L
    3, 5, 7, 6, // J
    2, 3, 4, 5, // O
};

bool check()
{
    for (int i = 0; i < 4; i++)
        if (a[i].x < 0 || a[i].x >= N || a[i].y >= M)
            return false;
        else if (field[a[i].y][a[i].x])
            return false;

    return true;
}

void drawBlock(sf::RenderWindow &window, sf::Sprite &s, int colorNum, int x, int y, int offsetX, int offsetY)
{
    s.setTextureRect(sf::IntRect((colorNum - 1) * 18, 0, 18, 18));
    s.setPosition(x * 18 + offsetX, y * 18 + offsetY);
    window.draw(s);
}

int main()
{
    srand(static_cast<unsigned>(time(0)));

    sf::RenderWindow window(sf::VideoMode(320, 480), "Tetris");

    // Calculate initial spawn position based on window size
    int spawnX = N / 2;
    int spawnY = 0;

    int windowWidth = window.getSize().x;
    int windowHeight = window.getSize().y;

    // Center the game field on the window
    int offsetX = (windowWidth - N * 18) / 2;
    int offsetY = (windowHeight - M * 18) / 2;

    // Center the field image on the window
    int fieldOffsetX = (windowWidth - N * 18) / 2;
    int fieldOffsetY = (windowHeight - M * 18) / 2;

    // Center the preview on the window
    int previewOffsetX = 5;
    int previewOffsetY = 5;

    sf::Texture t, t2;
    if (!t.loadFromFile("Textures/tiles.png") || !t2.loadFromFile("Textures/frame.png"))
    {
        // Error loading textures
        return -1;
    }
    sf::Sprite s(t), frame(t2);
    s.setTextureRect(sf::IntRect(0, 0, 18, 18));

    int dx = 0;
    bool rotate = false;
    int colorNum = 1;
    float timer = 0, delay = 0.3;

    sf::Clock clock;

    int nextBlock = rand() % 7;

    for (int i = 0; i < 4; i++)
    {
        a[i].x = figures[0][i] % 2 + spawnX;
        a[i].y = figures[0][i] / 2 + spawnY;
    }

    while (window.isOpen())
    {
        float time = clock.restart().asSeconds();
        timer += time;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Up)
                    rotate = true;
                else if (event.key.code == sf::Keyboard::Left)
                    dx = -1;
                else if (event.key.code == sf::Keyboard::Right)
                    dx = 1;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            delay = 0.05;
        else
            delay = 0.3; // Reset delay if Down key is released

        // <- Move -> //
        for (int i = 0; i < 4; i++)
        {
            b[i] = a[i];
            a[i].x += dx;
        }
        if (!check())
            for (int i = 0; i < 4; i++)
                a[i] = b[i];

        // Rotate //
        if (rotate)
        {
            Point p = a[1]; // center of rotation
            for (int i = 0; i < 4; i++)
            {
                int x = a[i].y - p.y;
                int y = a[i].x - p.x;
                a[i].x = p.x - x;
                a[i].y = p.y + y;
            }
            if (!check())
                for (int i = 0; i < 4; i++)
                    a[i] = b[i];
        }

        // Tick //
        if (timer > delay)
        {
            for (int i = 0; i < 4; i++)
            {
                b[i] = a[i];
                a[i].y += 1;
            }
            if (!check())
            {
                for (int i = 0; i < 4; i++)
                    field[b[i].y][b[i].x] = colorNum;

                colorNum = 1 + rand() % 7;
                int n = nextBlock;
                nextBlock = rand() % 7;

                for (int i = 0; i < 4; i++)
                {
                    a[i].x = figures[n][i] % 2 + spawnX;
                    a[i].y = figures[n][i] / 2 + spawnY;
                }
            }
            timer = 0;
        }

        // Check lines //
        int k = M - 1;
        for (int i = M - 1; i > 0; i--)
        {
            int count = 0;
            for (int j = 0; j < N; j++)
            {
                if (field[i][j])
                    count++;
                field[k][j] = field[i][j];
            }
            if (count < N)
                k--;
        }

        dx = 0;
        rotate = false;

        window.clear(sf::Color::Black);

        // Draw the preview of the next block
        for (int i = 0; i < 4; i++)
        {
            drawBlock(window, s, nextBlock + 1, figures[nextBlock][i] % 2, figures[nextBlock][i] / 2, previewOffsetX, previewOffsetY);
        }

        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
            {
                if (field[i][j] == 0)
                    continue;
                drawBlock(window, s, field[i][j], j, i, offsetX, offsetY);
            }

        for (int i = 0; i < 4; i++)
        {
            drawBlock(window, s, colorNum, a[i].x, a[i].y, offsetX, offsetY);
        }

        window.draw(frame);
        window.display();
    }

    return 0;
}