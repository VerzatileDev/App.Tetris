#include "Engine.h"
#include <ctime>

Engine::Engine() : eventHandler(EventHandler::getInstance()) {}

Engine::~Engine() {}

void Engine::initialize() {
    srand(static_cast<unsigned>(time(0)));

    Window::getInstance().initialize(620, 780, 18, M, N);

    inputSystem.Initialize();

    if (!texture.loadFromFile("Assets/Sprites/tiles.png") || !frameTexture.loadFromFile("Assets/Sprites/frame.png")) {
        // Error loading textures
        exit(-1);
    }

    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 18, 18));
    frame.setTexture(frameTexture);

    colorNum = 1;
    nextBlock = rand() % 7;
    timer = 0.0f;

    // Initialize the first piece
    int spawnX = N / 2;
    int spawnY = 0;
    for (int i = 0; i < 4; i++) {
        a[i].x = figures[0][i] % 2 + spawnX;
        a[i].y = figures[0][i] / 2 + spawnY;
    }
}

void Engine::update() {
    while (Window::getInstance().getWindow().isOpen() && eventHandler.IsRunning()) {
        float time = clock.restart().asSeconds();
        timer += time;

        inputSystem.Update();

        // Set DX and other controls
        int dx = eventHandler.getDx();

        // Move
        for (int i = 0; i < 4; i++) {
            b[i] = a[i];
            a[i].x += dx;
        }
        if (!check())
            for (int i = 0; i < 4; i++)
                a[i] = b[i];

        // Rotate
        if (eventHandler.isRotate()) {
            Point p = a[1];
            for (int i = 0; i < 4; i++) {
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

        // Tick
        if (timer > eventHandler.getDelay()) {
            for (int i = 0; i < 4; i++) {
                b[i] = a[i];
                a[i].y += 1;
            }
            if (!check()) {
                for (int i = 0; i < 4; i++)
                    field[b[i].y][b[i].x] = colorNum;

                audioManager.playBlockPlacementSound();

                colorNum = nextBlock + 1;
                int n = nextBlock;
                nextBlock = rand() % 7;

                for (int i = 0; i < 4; i++) {
                    a[i].x = figures[n][i] % 2 + N / 2;
                    a[i].y = figures[n][i] / 2;
                }
            }
            timer = 0;
        }

        // Check lines
        int k = M - 1;
        for (int i = M - 1; i > 0; i--) {
            int count = 0;
            for (int j = 0; j < N; j++) {
                if (field[i][j])
                    count++;
                field[k][j] = field[i][j];
            }
            if (count < N)
                k--;
            else
                audioManager.playLineClearSound();
        }

        eventHandler.getInstance().ProcessEvents();

        Window::getInstance().clear();

        // Draw the preview of the next block
        for (int i = 0; i < 4; i++) {
            drawBlock(sprite, nextBlock + 1, figures[nextBlock][i] % 2, figures[nextBlock][i] / 2, 5, 5);
        }

        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (field[i][j] == 0)
                    continue;
                drawBlock(sprite, field[i][j], j, i, (Window::getInstance().getWindow().getSize().x - N * 18) / 2, (Window::getInstance().getWindow().getSize().y - M * 18) / 2);
            }
        }

        for (int i = 0; i < 4; i++) {
            drawBlock(sprite, colorNum, a[i].x, a[i].y, (Window::getInstance().getWindow().getSize().x - N * 18) / 2, (Window::getInstance().getWindow().getSize().y - M * 18) / 2);
        }

        // Center the frame
        int frameOffsetX = (Window::getInstance().getWindow().getSize().x - frameTexture.getSize().x) / 2;
        int frameOffsetY = (Window::getInstance().getWindow().getSize().y - frameTexture.getSize().y) / 2;
        frame.setPosition(frameOffsetX, frameOffsetY);

        // Draw the frame
        Window::getInstance().getWindow().draw(frame);
        Window::getInstance().display();
    }
}

void Engine::drawBlock(sf::Sprite& s, int colorNum, int x, int y, int offsetX, int offsetY) {
    s.setTextureRect(sf::IntRect((colorNum - 1) * 18, 0, 18, 18));
    s.setPosition(x * 18 + offsetX, y * 18 + offsetY);
    Window::getInstance().getWindow().draw(s);
}

bool Engine::check() {
    for (int i = 0; i < 4; i++)
        if (a[i].x < 0 || a[i].x >= N || a[i].y >= M)
            return false;
        else if (field[a[i].y][a[i].x])
            return false;

    return true;
}