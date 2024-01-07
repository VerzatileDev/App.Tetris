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
    bool IsRunning();
    void ProcessEvents(); // Process the events in the event queue
    
    // Temporary Eventhandler variables For Player Related Movement
    float getDelay();
    bool isRotate();
    int getDx();
    bool rotate = false;
private:
    // References to the subsystem
    std::vector<Event> eventQueue;
    SubSystem* subsystemRef = nullptr;

    bool running = true; // GAME loop Status

    // Temporary Eventhandler variables For Player Related Movement
    float delay = 0.3f; // Defines The Player blocks falling speed
    float dx = 0; // Defines The Player blocks movement speed
};
