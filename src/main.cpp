#include <iostream>
#include "GamepadEventDispatcher.h"


int main() {
    dualshock4::GamepadEventDispatcher eventDispatcher{};

    eventDispatcher.start();

    eventDispatcher.registerEventHandler(dualshock4::KeyEvent::KEY_SOUTH, []() {
        std::cout << std::this_thread::get_id() << "\n";
    });


    std::cout << std::this_thread::get_id() << "\n";
    return 0;
}