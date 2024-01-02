#pragma once

// System Libraries
#include <string>

/// <summary>
/// <title>Event</title>
/// 
/// <para>
/// Class storing Events that can be passed to the EventManager,
/// use the following to make new Event types <br/>
/// </para>
/// 
/// <note>
/// Currently only supports KeyPressed, KeyHeldDown, KeyReleased, and Closed
/// And get type of Event and the key string of the Event
/// </note>
/// 
/// </summary>
class Event {
public:
    enum EventType {
        Closed,
        KeyPressed,
        KeyHeldDown,
        KeyReleased,
    };

    Event(EventType type, std::string keyString);
    Event(EventType type);
    EventType GetType() const;
    std::string GetKeyString() const;

private:
    EventType type;
    std::string keyString;
};