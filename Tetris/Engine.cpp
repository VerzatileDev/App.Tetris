#include "Engine.h"
#include <ctime>

Engine::Engine() : eventHandler(EventHandler::getInstance()) {}

Engine::~Engine() {}

void Engine::initialize() {
    srand(static_cast<unsigned>(time(0)));

    // Initialize the window with the same dimensions
    Window::getInstance().initialize(420, 480, 18, M, N);

    inputSystem.Initialize();

    if (!texture.loadFromFile("Assets/Sprites/tiles.png")) {
        // Error loading textures
        std::cerr << "Error: Failed to load texture 'Assets/Sprites/tiles.png'." << std::endl;
        return; // Exit gracefully instead of terminating
    }

    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 18, 18));

    colorNum = 1;
    nextBlock = rand() % 7;
    timer = 0.0f;
    score = 0;

    // Initialize the first piece at the top-left corner of the field
    int spawnX = N / 2; // Center horizontally
    int spawnY = 0;     // Top of the field
    for (int i = 0; i < 4; i++) {
        a[i].x = figures[0][i] % 2 + spawnX;
        a[i].y = figures[0][i] / 2 + spawnY;
    }

    // Clear the field
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            field[i][j] = 0;
        }
    }
}

void Engine::update() {
    while (Window::getInstance().getWindow().isOpen() && eventHandler.IsRunning()) {
        float time = clock.restart().asSeconds();
        timer += time;

        inputSystem.Update();

        // Handle horizontal movement
        int dx = eventHandler.getDx();
        for (int i = 0; i < 4; i++) {
            b[i] = a[i];
            a[i].x += dx;
        }
        if (!check())
            for (int i = 0; i < 4; i++)
                a[i] = b[i];

        // Handle rotation
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

        // Handle block falling
        if (timer > eventHandler.getDelay()) {
            for (int i = 0; i < 4; i++) {
                b[i] = a[i];
                a[i].y += 1;
            }
            if (!check()) {
                for (int i = 0; i < 4; i++)
                    field[b[i].y][b[i].x] = colorNum; // Lock the block into place

                audioManager.playBlockPlacementSound();

                // Prepare the next block
                colorNum = nextBlock + 1;
                int n = nextBlock;
                nextBlock = rand() % 7;

                for (int i = 0; i < 4; i++) {
                    a[i].x = figures[n][i] % 2 + N / 2;
                    a[i].y = figures[n][i] / 2;
                }

                // Check for game over (new block overlaps existing blocks)
                if (!check()) {
                    // Clear the field
                    for (int i = 0; i < M; i++) {
                        for (int j = 0; j < N; j++) {
                            field[i][j] = 0; // Reset all cells to 0
                        }
                    }

                    // Reset the score
                    score = 0;
                }
            }
            timer = 0;
        }

        // Check for and clear completed lines
        int tempField[M][N] = { 0 }; // Temporary array to store the updated field state
        int k = M - 1; // Start from the bottom of the field

        for (int i = M - 1; i >= 0; i--) {
            int count = 0;
            for (int j = 0; j < N; j++) {
                if (field[i][j])
                    count++;
                tempField[k][j] = field[i][j]; // Copy the row to the temporary array
            }
            if (count < N)
                k--; // Move to the next row if the current row is not full
            else {
                audioManager.playLineClearSound();
                score++; // Increment score when a line is cleared
            }
        }

        // Check for win condition BEFORE copying tempField back to field
        if (score >= 10) {
            // Reset the score
            score = 0;

            // Clear the field
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < N; j++) {
                    field[i][j] = 0; // Reset all cells to 0
                }
            }

            // Prepare the next block
            colorNum = nextBlock + 1;
            int n = nextBlock;
            nextBlock = rand() % 7;

            for (int i = 0; i < 4; i++) {
                a[i].x = figures[n][i] % 2 + N / 2;
                a[i].y = figures[n][i] / 2;
            }

            // Skip copying tempField back to field since the field is already cleared
        }
        else {
            // Copy the updated field state back to the original field array
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < N; j++) {
                    field[i][j] = tempField[i][j];
                }
            }
        }

        eventHandler.getInstance().ProcessEvents();

        Window::getInstance().clear();

        // Draw the playable area border
        sf::RectangleShape playableAreaBorder(sf::Vector2f(N * 18, M * 18));
        playableAreaBorder.setPosition(18, 18);
        playableAreaBorder.setFillColor(sf::Color::Transparent);
        playableAreaBorder.setOutlineColor(sf::Color::White);
        playableAreaBorder.setOutlineThickness(2);
        Window::getInstance().getWindow().draw(playableAreaBorder);

        // Draw the preview area border
        sf::RectangleShape previewAreaBorder(sf::Vector2f(6 * 18, 6 * 18));
        previewAreaBorder.setPosition(N * 18 + 28, 18);
        previewAreaBorder.setFillColor(sf::Color::Transparent);
        previewAreaBorder.setOutlineColor(sf::Color::White);
        previewAreaBorder.setOutlineThickness(2);
        Window::getInstance().getWindow().draw(previewAreaBorder);

        // Draw the preview of the next block
        int previewCenterX = N * 18 + 28 + (6 * 18) / 2 - 18;
        int previewCenterY = 18 + (6 * 18) / 2 - 18 - 18;
        for (int i = 0; i < 4; i++) {
            drawBlock(sprite, nextBlock + 1, figures[nextBlock][i] % 2, figures[nextBlock][i] / 2, previewCenterX, previewCenterY);
        }

        // Draw the score under the preview area
        sf::Text scoreText;
        sf::Font font;
        if (!font.loadFromFile("Assets/Fonts/arial.ttf")) {
            exit(-1); // Error loading font
        }
        scoreText.setFont(font);
        scoreText.setString("Score: " + std::to_string(score));
        scoreText.setCharacterSize(18);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(N * 18 + 28, 18 + 6 * 18 + 10); // Position under the preview area
        Window::getInstance().getWindow().draw(scoreText);

        // Draw the game field
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (field[i][j] == 0)
                    continue;
                drawBlock(sprite, field[i][j], j, i, 18, 18);
            }
        }

        // Draw the current falling block
        for (int i = 0; i < 4; i++) {
            drawBlock(sprite, colorNum, a[i].x, a[i].y, 18, 18);
        }

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