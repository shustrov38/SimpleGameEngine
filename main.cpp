#include "Window.h"
#include "Engine.h"

int main() {
    Engine engine;

    while (!engine.isDone()) {
        engine.update();
    }

    return 0;
}