#include "Window.h"
#include <iostream>

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

    window.create(sf::VideoMode(width, height), "TETRIS", sf::Style::Titlebar | sf::Style::Close);
    windowSize.x = width;
    windowSize.y = height;

    // Additional window setup can be done here
    window.setFramerateLimit(60);

    // Calculate initial offsets for centering
    offsetX = (width - columns * tileSize) / 2;
    offsetY = (height - rows * tileSize) / 2;
    
    // Set window Icon
    setIcon("Assets/Icons/VerzaTetrisWindow.png");
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

void Window::setIcon(const std::string& iconPath) {
    sf::Image icon;
    if (icon.loadFromFile(iconPath)) {
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }
    else {
        // Handle error (e.g., log or throw an exception)
        std::cerr << "Failed to load icon from: " << iconPath << std::endl;
    }
}