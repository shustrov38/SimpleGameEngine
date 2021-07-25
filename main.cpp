#include "Window.h"
#include "Engine.h"

int main() {
    Engine engine;

    while (!engine.isDone()) {
        engine.handleInput();
        engine.update(30);
        engine.render();
        engine.restartClock();
    }

    return 0;
}