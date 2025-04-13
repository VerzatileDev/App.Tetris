#include "Engine.h"

int main()
{
    Engine engine;
    engine.initialize();
	engine.setWinConditionEnabled(false); // When Reaching 10 points, the game ends (Resets)
    engine.update();
    return 0;
}
