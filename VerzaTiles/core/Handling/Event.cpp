#include "Event.h"

Event::Event(EventType type, std::string keyString)
    : type(type), keyString(keyString) {}

Event::Event(EventType type)
    : type(type), keyString("Unknown Key") {}

Event::EventType Event::GetType() const {
    return type;
}

std::string Event::GetKeyString() const {
    return keyString;
}
