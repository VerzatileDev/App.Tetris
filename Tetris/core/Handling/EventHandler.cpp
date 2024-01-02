#include "EventHandler.h"

EventHandler::EventHandler() : subsystemRef(nullptr) 
{

}

EventHandler::EventHandler(SubSystem& subsystem) : subsystemRef(&subsystem) 
{

}

EventHandler::~EventHandler()
{

}

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

void EventHandler::ProcessEvents() {
    for (Event& event : eventQueue) {
        switch (event.GetType()) {
        case Event::Closed:
            std::cout << "Closing the Engine" << std::endl;
            //running = false;
            break;
        case Event::KeyPressed:
            if (event.GetKeyString() == "Escape") {
                std::cout << "Closing the Engine" << std::endl;
                //running = false;
            }
            else if (event.GetKeyString() == "Space") {
				//std::cout << "Space is pressed" << std::endl;
				//player.jump();
			}
            break;
        case Event::KeyHeldDown:
            if (event.GetKeyString() == "A") {
                //std::cout << "A is held down" << std::endl;   
                //player.moveLeft();
            }
            else if (event.GetKeyString() == "D") {
                //std::cout << "D is held down" << std::endl;
                //player.moveRight();
            }

            break;
        case Event::KeyReleased:
            if (event.GetKeyString() == "A" || event.GetKeyString() == "D") {
                //player.stopMoving();
            }
            else if (event.GetKeyString() == "Space") {
				//canJump = true;
			}
            break;
        default:
            std::cout << "Event not defined with an action " << std::endl;
            break;
        }
    }
    ClearEvents();
}