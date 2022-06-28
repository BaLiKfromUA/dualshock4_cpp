#include <cstdio>
#include <functional>
#include <cstring>
#include <cassert>
#include <iostream>
#include "hidapi.h"
#include "GamepadEventDispatcher.h"



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

Gamepad CurGamepad{};
LedState LedState{};

void GamepadSearch() {
    struct hid_device_info *cur_dev;
    cur_dev = hid_enumerate(SONY_VENDOR, 0x0);
    while (cur_dev) {
        // todo: find by BT
        if (cur_dev->product_id == SONY_DS4_USB || cur_dev->product_id == SONY_DS4_V2_USB) {
            CurGamepad.HidHandle = hid_open(cur_dev->vendor_id, cur_dev->product_id, cur_dev->serial_number);
            assert(CurGamepad.HidHandle != nullptr && "Failed to open HID!");
            hid_set_nonblocking(CurGamepad.HidHandle, 1);
            CurGamepad.ControllerType = SONY_DUALSHOCK4;
            CurGamepad.USBConnection = true;
            break;
        }
        cur_dev = cur_dev->next;
    }
    if (cur_dev) {
        hid_free_enumeration(cur_dev);
    }
}

void GamepadSetState(struct LedState OutState) {
    assert(CurGamepad.HidHandle != nullptr);

    if (CurGamepad.ControllerType == SONY_DUALSHOCK4 && CurGamepad.USBConnection) {
        unsigned char outputReport[31];
        memset(outputReport, 0, 31);

        outputReport[0] = 0x05;
        outputReport[1] = 0xff;
        outputReport[4] = 0; //OutState.SmallMotor;
        outputReport[5] = 0; //OutState.LargeMotor;
        outputReport[6] = std::clamp(OutState.LEDRed - OutState.LEDBrightness, 0, 255);
        outputReport[7] = std::clamp(OutState.LEDGreen - OutState.LEDBrightness, 0, 255);
        outputReport[8] = std::clamp(OutState.LEDBlue - OutState.LEDBrightness, 0, 255);

        hid_write(CurGamepad.HidHandle, outputReport, 31);
    } // todo: BT
}

int main() {
    dualshock4::GamepadEventDispatcher eventDispatcher{};

    eventDispatcher.start();

    eventDispatcher.registerEventHandler(dualshock4::KeyEvent::KEY_SOUTH, []() {
        std::cout << std::this_thread::get_id() << "\n";
    });


    std::cout <<  std::this_thread::get_id() << "\n";
    return 0;
}