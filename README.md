# dualshock4_cpp
my trial to get any user input from DualShock 4 v2


In progress of development for Linux...

## Usage example

```cpp
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
```


## Dependencies
- [hidapi](https://github.com/libusb/hidapi) - simple library for communicating with USB and Bluetooth HID devices.
```
    sudo apt install libhidapi-dev
```
- [eventpp](https://github.com/wqking/eventpp) - event dispatcher for C++.

## References

- [Event documentation](https://www.psdevwiki.com/ps4/DS4-USB)
- [PS dev wiki page](https://www.psdevwiki.com/ps4/DualShock_4)
- [Gentoo wiki page](https://wiki.gentoo.org/wiki/Sony_DualShock)
