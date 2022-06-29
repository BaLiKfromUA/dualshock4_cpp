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

#define SONY_DS4_MASK_UP 0x00001
#define SONY_DS4_MASK_DOWN 0x00002
#define SONY_DS4_MASK_LEFT 0x00004
#define SONY_DS4_MASK_RIGHT 0x00008
#define SONY_DS4_MASK_S 0x01000
#define SONY_DS4_MASK_E 0x02000
#define SONY_DS4_MASK_W 0x04000
#define SONY_DS4_MASK_N 0x08000


#define SONY_DS4_OFFSET_UP 0
#define SONY_DS4_OFFSET_DOWN 1
#define SONY_DS4_OFFSET_LEFT 2
#define SONY_DS4_OFFSET_RIGHT 3
#define SONY_DS4_OFFSET_S 12
#define SONY_DS4_OFFSET_E 13
#define SONY_DS4_OFFSET_W 14
#define SONY_DS4_OFFSET_N 15

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
    public:
        using buttonsMask = int;
    private:
        internal::Gamepad curGamepad{};
        internal::LedState ledState{};

        buttonsMask lastButtonState = 0;

    public:
        void gamepadSearch();

        void updateButtonState();

        void gamepadSetState(struct internal::LedState OutState);
    };
}


#endif //DUALSHOCK4_CPP_GAMEPADMANAGER_H
