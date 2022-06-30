#include <iostream>
#include "GamepadEventDispatcher.h"


int main() {
    dualshock4::GamepadEventDispatcher eventDispatcher{};

    eventDispatcher.registerEventHandler(dualshock4::KEY_UP, []() {
        std::cout << "↑\n";
    });

    eventDispatcher.registerEventHandler(dualshock4::KEY_DOWN, []() {
        std::cout << "↓\n";
    });

    eventDispatcher.registerEventHandler(dualshock4::KEY_LEFT, []() {
        std::cout << "←\n";
    });

    eventDispatcher.registerEventHandler(dualshock4::KEY_RIGHT, []() {
        std::cout << "→\n";
    });

    eventDispatcher.registerEventHandler(dualshock4::KEY_NORTH, []() {
        std::cout << "△\n";
    });

    eventDispatcher.registerEventHandler(dualshock4::KEY_SOUTH, []() {
        std::cout << "✕\n";
    });

    eventDispatcher.registerEventHandler(dualshock4::KEY_EAST, []() {
        std::cout << "○\n";
    });

    eventDispatcher.registerEventHandler(dualshock4::KEY_WEST, []() {
        std::cout << "□\n";
    });

    eventDispatcher.start();
    eventDispatcher.wait();

    return 0;
}