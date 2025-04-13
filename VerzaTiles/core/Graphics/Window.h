#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>

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

    void setIcon(const std::string& iconPath);

private:
    Window();

    sf::RenderWindow window;
    sf::Vector2u windowSize;
    int offsetX, offsetY;  // Added for centering
};