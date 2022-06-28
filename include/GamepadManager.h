//
// Created by balik on 28.06.22.
//

#ifndef DUALSHOCK4_CPP_GAMEPADMANAGER_H
#define DUALSHOCK4_CPP_GAMEPADMANAGER_H

#include <cstdio>
#include <functional>
#include <cstring>
#include <cassert>
#include "hidapi.h"

// PS4 stuff
// http://www.psdevwiki.com/ps4/DS4-USB
// http://www.psdevwiki.com/ps4/DS4-BT
// http://eleccelerator.com/wiki/index.php?title=DualShock_4
// and a little bit of https://github.com/chrippa/ds4drv
#define SONY_DUALSHOCK4                    27

#define SONY_VENDOR 0x054C
#define SONY_DS4_USB 0x05C4
#define SONY_DS4_V2_USB 0x09CC
#define SONY_DS4_BT 0x081F

namespace dualshock4 {

    namespace internal {
        struct Gamepad {
            hid_device *HidHandle;
            unsigned short ControllerType; // todo: WORD
            bool USBConnection;
            unsigned char BatteryMode;
            unsigned char BatteryLevel;
            wchar_t *serial_number;
        };

        struct LedState {
            unsigned char LEDRed;
            unsigned char LEDGreen;
            unsigned char LEDBlue;
            unsigned char LEDBrightness;
        };
    }

    class GamepadManager {
    private:
        internal::Gamepad curGamepad{};
        internal::LedState ledState{};
    public:
        void gamepadSearch();

        void gamepadSetState(struct internal::LedState OutState);
    };
}


#endif //DUALSHOCK4_CPP_GAMEPADMANAGER_H
