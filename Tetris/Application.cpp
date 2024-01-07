// Project Includes
#include "core/Graphics/Window.h"
#include "core/Audio/AudioManager.h"

// System Libraries
#include <time.h>
#include "core/Handling/EventHandler.h"
#include "core/Inputs/InputSystem.h"

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

void drawBlock(sf::Sprite& s, int colorNum, int x, int y, int offsetX, int offsetY)
{
    s.setTextureRect(sf::IntRect((colorNum - 1) * 18, 0, 18, 18));
    s.setPosition(x * 18 + offsetX, y * 18 + offsetY);
    Window::getInstance().getWindow().draw(s);
}

int main()
{
    srand(static_cast<unsigned>(time(0)));

    Window::getInstance().initialize(320, 480, 18, M, N); // Initialize the window Creates the window, if not initialized already

    EventHandler& eventHandler = EventHandler::getInstance();
    InputSystem inputSystem;
    AudioManager audioManager;
    inputSystem.Initialize();

    // Calculate initial spawn position based on window size
    int spawnX = N / 2;
    int spawnY = 0;

    int windowWidth = Window::getInstance().getWindow().getSize().x;
    int windowHeight = Window::getInstance().getWindow().getSize().y;

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
    if (!t.loadFromFile("Assets/Sprites/tiles.png") || !t2.loadFromFile("Assets/Sprites/frame.png"))
    {
        // Error loading textures
        return -1;
    }
    sf::Sprite s(t), frame(t2);
    s.setTextureRect(sf::IntRect(0, 0, 18, 18));

    int dx = 0;
    int colorNum = 1;
    float timer = 0;
    sf::Clock clock;

    int nextBlock = rand() % 7;

    for (int i = 0; i < 4; i++)
    {
        a[i].x = figures[0][i] % 2 + spawnX;
        a[i].y = figures[0][i] / 2 + spawnY;
    }

    while (Window::getInstance().getWindow().isOpen() && eventHandler.IsRunning())
    {
        float time = clock.restart().asSeconds();
        timer += time;

        inputSystem.Update();
        // Set DX On EventHandler to this Class or file. 
        // Set Rotate on EventHandler to this Class or file.
        // Set Delay on EventHandler to this Class or file.

        // CHANGE THESE TO BE SETTERS FROM THIS CLASS rather than getting from the event handler
        // Maybe

        // Set DX from EventHandler
        dx = eventHandler.getDx();

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
        if (eventHandler.isRotate())
        {
            Point p = a[1]; // center of rotation
            for (int i = 0; i < 4; i++)
            {
                int x = a[i].y - p.y;
                int y = a[i].x - p.x;
                a[i].x = p.x - x;
                a[i].y = p.y + y;
            }

            audioManager.playRotateSound();

            if (!check())
                for (int i = 0; i < 4; i++)
                    a[i] = b[i];
        }

        // Tick //
        if (timer > eventHandler.getDelay())
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

                audioManager.playBlockPlacementSound();

                colorNum = nextBlock + 1;
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
            else
            {
                audioManager.playLineClearSound();
            }
        }

        eventHandler.getInstance().ProcessEvents();

        Window::getInstance().clear();

        // Draw the preview of the next block
        for (int i = 0; i < 4; i++)
        {
            drawBlock(s, nextBlock + 1, figures[nextBlock][i] % 2, figures[nextBlock][i] / 2, previewOffsetX, previewOffsetY);
        }

        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
            {
                if (field[i][j] == 0)
                    continue;
                drawBlock(s, field[i][j], j, i, offsetX, offsetY);
            }

        for (int i = 0; i < 4; i++)
        {
            drawBlock(s, colorNum, a[i].x, a[i].y, offsetX, offsetY);
        }

        Window::getInstance().getWindow().draw(frame);
        Window::getInstance().display();
    }

    return 0;
}
