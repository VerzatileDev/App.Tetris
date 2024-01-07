#include "EventHandler.h"

EventHandler::EventHandler() : subsystemRef(nullptr) 
{}

EventHandler::EventHandler(SubSystem& subsystem) : subsystemRef(&subsystem) 
{}

EventHandler::~EventHandler()
{}

EventHandler& EventHandler::getInstance() {
    static EventHandler instance;
    return instance;
}

void EventHandler::AddEvent(const Event& event) {
    eventQueue.push_back(event);
}

void EventHandler::ClearEvents() {
    eventQueue.clear();
}

bool EventHandler::IsRunning() {
    return running;
}

void EventHandler::ProcessEvents() {
    for (Event& event : eventQueue) {
        switch (event.GetType()) {
        case Event::Closed:
            std::cout << "Closing the Engine" << std::endl;
            running = false;
            break;
        case Event::KeyPressed:
            if (event.GetKeyString() == "Escape") {
                std::cout << "Closing the Engine" << std::endl;
                running = false;
            }
            else if (event.GetKeyString() == "Space" || event.GetKeyString() == "W") {
                rotate = false;
			}
            else if (event.GetKeyString() == "A") 
            {
                dx = -1;
            }
            else if (event.GetKeyString() == "D")
            {
                dx = 1;

            }
            else if (event.GetKeyString() == "S")
            {
                delay = 0.05;
			}
            break;
        case Event::KeyReleased:
            if (event.GetKeyString() == "A" || event.GetKeyString() == "D") {
                dx = 0;
            }
            else if (event.GetKeyString() == "Space" || event.GetKeyString() == "W") {
                rotate = true;
            }
            else if (event.GetKeyString() == "S") {
				delay = 0.3;
			}
            break;
        default:
            break;
        }
    }
    ClearEvents();
}

float EventHandler::getDelay()
{
    return delay;
}

bool EventHandler::isRotate()
{
    bool currentRotate = rotate;  // Store the current state
    rotate = false;  // Reset rotate to false after reading its state
    return currentRotate;  // Return the stored state
}

int EventHandler::getDx()
{
    float tempDx = dx;  // Store the current state
    dx = 0;  // Reset dx to 0 after reading its state
    return tempDx;
}
