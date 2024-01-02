#pragma once

// Included Files
#include "Event.h"
#include "../SubSystem.h"

// System Libraries
#include <vector>
#include <iostream>
#include <functional> 


class EventHandler {
public:
    EventHandler(); // Default Constructor
    EventHandler(SubSystem& subsystem); // Constructor with subsystem reference
    ~EventHandler(); // Destructor
    static EventHandler& getInstance(); // Get the instance of the EventHandler (Singleton)
    void AddEvent(const Event& event); // Add an event to the event queue from the base list of Event class  to be processed 
    void ClearEvents(); // Clear the event queue
    void ProcessEvents(); // Process the events in the event queue

private:
    std::vector<Event> eventQueue;
    SubSystem* subsystemRef = nullptr;
};
