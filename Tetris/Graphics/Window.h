#pragma once
#include <SFML/Graphics.hpp>

class Window {
public:
    ~Window();
    static Window& getInstance();

    void initialize(int width, int height, int tileSize, int rows, int columns);
    void clear();
    void display();
    sf::RenderWindow& getWindow();

    void setFullscreen(bool fullscreen);
    void setWindowSize(sf::Vector2u size);

private:
    Window();

    sf::RenderWindow window;
    sf::Vector2u windowSize;
    int offsetX, offsetY;  // Added for centering
};