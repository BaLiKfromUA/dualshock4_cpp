#include <iostream>
#include "GamepadEventDispatcher.h"


int main() {
    dualshock4::GamepadEventDispatcher eventDispatcher{};

    eventDispatcher.start();
    eventDispatcher.wait();

    return 0;
}