#include "Window.h"

Window::Window() : window(sf::VideoMode(320, 480), "TETRIS"), windowSize(320, 480) {}

Window::~Window() {
    if (window.isOpen()) {
        window.close();
    }
}

Window& Window::getInstance() {
    static Window instance;
    return instance;
}

void Window::initialize(int width, int height, int tileSize, int rows, int columns) {

    window.create(sf::VideoMode(width, height), "TETRIS");
    windowSize.x = width;
    windowSize.y = height;

    // Additional window setup can be done here
    window.setFramerateLimit(60);

    // Calculate initial offsets for centering
    offsetX = (width - columns * tileSize) / 2;
    offsetY = (height - rows * tileSize) / 2;
}

void Window::clear() {
    window.clear();
}

void Window::display() {
    window.display();
}

sf::RenderWindow& Window::getWindow() {
    return window;
}

void Window::setFullscreen(bool fullscreen) {
    window.create(fullscreen ? sf::VideoMode::getFullscreenModes()[0] : sf::VideoMode(windowSize.x, windowSize.y), "SFML + Box2D", fullscreen ? sf::Style::Fullscreen : sf::Style::Default);
    windowSize = window.getSize();
}

void Window::setWindowSize(sf::Vector2u size) {
    window.setSize(size);
    windowSize = size;
}