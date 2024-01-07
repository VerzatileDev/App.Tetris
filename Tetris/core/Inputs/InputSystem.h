#pragma once

// System libraries
#include <unordered_map>
#include <iostream>
#include <bitset>

// Included Libraries
#include <SFML/Window/Keyboard.hpp>

// Included Files
#include "../Handling/Event.h"
#include "../Graphics/Window.h"
#include "../Handling/EventHandler.h"

class InputSystem {
public:
    void Initialize();
    void Update();
    void PollEvents();
    void Cleanup();

    void UpdateKeyState(sf::Keyboard::Key keyCode, bool isPressed);
    bool IsKeyDown(sf::Keyboard::Key keyCode);
    bool WasKeyDown(sf::Keyboard::Key keyCode);

private:
    std::unordered_map<sf::Keyboard::Key, std::string> keyCodeMap;
    std::string ConvertSFMLKeyCodeToString(sf::Keyboard::Key keyCode);
    std::unordered_map<sf::Keyboard::Key, std::string> GenerateKeyCodeMap();

    std::bitset<sf::Keyboard::KeyCount> keyState;
    std::bitset<sf::Keyboard::KeyCount> prevKeyState;
};