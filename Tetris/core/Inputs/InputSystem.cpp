#include "InputSystem.h"

void InputSystem::Initialize() {
    try {
        keyCodeMap = GenerateKeyCodeMap();
    }
    catch (const std::exception& e) {
        std::cerr << "An exception occurred during InputSystem initialization: " << e.what() << '\n';
    }
}

void InputSystem::Update() {
    try {
        PollEvents();
    }
    catch (const std::exception& e) {
        std::cerr << "An exception occurred during InputSystem update: " << e.what() << '\n';
    }
}

void InputSystem::PollEvents() {
    sf::Event event;
    while (Window::getInstance().getWindow().pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            std::cout << "Received close event" << std::endl;
            EventHandler::getInstance().AddEvent(Event(Event::Closed));
        }
        else if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) {
            auto it = keyCodeMap.find(event.key.code);
            if (it != keyCodeMap.end()) {
                bool isKeyDown = event.type == sf::Event::KeyPressed;

                if (isKeyDown && !IsKeyDown(event.key.code)) {
                    EventHandler::getInstance().AddEvent(Event(Event::KeyPressed, it->second));
                }
                else if (!isKeyDown) {
                    EventHandler::getInstance().AddEvent(Event(Event::KeyReleased, it->second));
                }

                UpdateKeyState(event.key.code, isKeyDown);

                if (IsKeyDown(event.key.code)) {
                    EventHandler::getInstance().AddEvent(Event(Event::KeyHeldDown, it->second));
                }
            }
            else {
                EventHandler::getInstance().AddEvent(Event(Event::KeyPressed, "Unknown Key"));
            }
        }
    }
}

std::string InputSystem::ConvertSFMLKeyCodeToString(sf::Keyboard::Key keyCode) {
    // Convert SFML KeyCodes to Strings for use in the EEventHandler and for debugging/ Use Case purposes (std::cout)
    if (keyCode >= sf::Keyboard::A && keyCode <= sf::Keyboard::Z) {
        return std::string(1, static_cast<char>(keyCode + 'A' - sf::Keyboard::A));
    }
    else if (keyCode >= sf::Keyboard::Num0 && keyCode <= sf::Keyboard::Num9) {
        return std::to_string(keyCode - sf::Keyboard::Num0);
    }
    else {
        switch (keyCode) {
        case sf::Keyboard::Space: return "Space";
        case sf::Keyboard::Enter: return "Enter";
        case sf::Keyboard::Backspace: return "Backspace";
        case sf::Keyboard::Escape: return "Escape";
        case sf::Keyboard::Tab: return "Tab";
        case sf::Keyboard::Left: return "Left Arrow";
        case sf::Keyboard::Right: return "Right Arrow";
        case sf::Keyboard::Up: return "Up Arrow";
        case sf::Keyboard::Down: return "Down Arrow";
        case sf::Keyboard::F1: return "F1";
        case sf::Keyboard::F2: return "F2";
        case sf::Keyboard::F3: return "F3";
        case sf::Keyboard::F4: return "F4";
        case sf::Keyboard::F5: return "F5";
        case sf::Keyboard::F6: return "F6";
        case sf::Keyboard::F7: return "F7";
        case sf::Keyboard::F8: return "F8";
        case sf::Keyboard::F9: return "F9";
        case sf::Keyboard::F10: return "F10";
        case sf::Keyboard::F11: return "F11";
        case sf::Keyboard::F12: return "F12";
        case sf::Keyboard::Num0: return "Num 0";
        case sf::Keyboard::Num1: return "Num 1";
        case sf::Keyboard::Num2: return "Num 2";
        case sf::Keyboard::Num3: return "Num 3";
        case sf::Keyboard::Num4: return "Num 4";
        case sf::Keyboard::Num5: return "Num 5";
        case sf::Keyboard::Num6: return "Num 6";
        case sf::Keyboard::Num7: return "Num 7";
        case sf::Keyboard::Num8: return "Num 8";
        case sf::Keyboard::Num9: return "Num 9";
        case sf::Keyboard::LControl: return "Left Control";
        case sf::Keyboard::LShift: return "Left Shift";
        case sf::Keyboard::LAlt: return "Left Alt";
        case sf::Keyboard::LSystem: return "Left System";
        case sf::Keyboard::RControl: return "Right Control";
        case sf::Keyboard::RShift: return "Right Shift";
        case sf::Keyboard::RAlt: return "Right Alt";
        case sf::Keyboard::RSystem: return "Right System";
        case sf::Keyboard::Menu: return "Menu";
        case sf::Keyboard::LBracket: return "Left Bracket";
        case sf::Keyboard::RBracket: return "Right Bracket";
        case sf::Keyboard::Semicolon: return "Semicolon";
        case sf::Keyboard::Comma: return "Comma";
        case sf::Keyboard::Period: return "Period";
        case sf::Keyboard::Quote: return "Quote";
        case sf::Keyboard::Slash: return "Slash";
        case sf::Keyboard::Backslash: return "Backslash";
        case sf::Keyboard::Tilde: return "Tilde";
        case sf::Keyboard::Equal: return "Equal";
        case sf::Keyboard::Hyphen: return "Hyphen";
        case sf::Keyboard::Pause: return "Pause";
        case sf::Keyboard::Insert: return "Insert";
        case sf::Keyboard::Home: return "Home";
        case sf::Keyboard::Delete: return "Delete";
        case sf::Keyboard::End: return "End";
        case sf::Keyboard::PageUp: return "Page Up";
        case sf::Keyboard::PageDown: return "Page Down";
        case sf::Keyboard::Numpad0: return "Numpad 0";
        case sf::Keyboard::Numpad1: return "Numpad 1";
        case sf::Keyboard::Numpad2: return "Numpad 2";
        case sf::Keyboard::Numpad3: return "Numpad 3";
        case sf::Keyboard::Numpad4: return "Numpad 4";
        case sf::Keyboard::Numpad5: return "Numpad 5";
        case sf::Keyboard::Numpad6: return "Numpad 6";
        case sf::Keyboard::Numpad7: return "Numpad 7";
        case sf::Keyboard::Numpad8: return "Numpad 8";
        case sf::Keyboard::Numpad9: return "Numpad 9";
        case sf::Keyboard::Add: return "Numpad +";
        case sf::Keyboard::Subtract: return "Numpad -";
        case sf::Keyboard::Multiply: return "Numpad *";
        case sf::Keyboard::Divide: return "Numpad /";
        default: return "Unknown Key";
        }
    }
}

std::unordered_map<sf::Keyboard::Key, std::string> InputSystem::GenerateKeyCodeMap() {
    std::unordered_map<sf::Keyboard::Key, std::string> map;

    // Generate the map of key codes and strings for each key code in the range of key codes supported by SFML (0 - 101)
    for (int keyEnum = 0; keyEnum < sf::Keyboard::KeyCount; ++keyEnum) {
        sf::Keyboard::Key key = static_cast<sf::Keyboard::Key>(keyEnum);
        map[key] = ConvertSFMLKeyCodeToString(key);
    }
    return map;
}

void InputSystem::UpdateKeyState(sf::Keyboard::Key keyCode, bool isPressed) {
    keyState.set(static_cast<size_t>(keyCode), isPressed);
}

bool InputSystem::IsKeyDown(sf::Keyboard::Key keyCode) {
    return keyState.test(static_cast<size_t>(keyCode));
}

void InputSystem::Cleanup() {
    keyCodeMap.clear();
}
