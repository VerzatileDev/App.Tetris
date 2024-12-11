#pragma once

#include "core/Graphics/Window.h"
#include "core/Audio/AudioManager.h"
#include "core/Handling/EventHandler.h"
#include "core/Inputs/InputSystem.h"
#include <SFML/Graphics.hpp>

class Engine
{
public:
    Engine();
    ~Engine();

    void initialize();
    void update();

private:
    void drawBlock(sf::Sprite& s, int colorNum, int x, int y, int offsetX, int offsetY);
    bool check();

    static const int M = 20;
    static const int N = 10;
    int field[M][N] = { 0 };

    struct Point {
        int x, y;
    } a[4], b[4];

    int figures[7][4] = {
        1, 3, 5, 7, // I
        2, 4, 5, 7, // Z
        3, 5, 4, 6, // S
        3, 5, 4, 7, // T
        2, 3, 5, 7, // L
        3, 5, 7, 6, // J
        2, 3, 4, 5  // O
    };

    int colorNum;
    int nextBlock;
    float timer;
    sf::Clock clock;
    sf::Texture texture, frameTexture;
    sf::Sprite sprite, frame;
    EventHandler& eventHandler;
    InputSystem inputSystem;
    AudioManager audioManager;
};