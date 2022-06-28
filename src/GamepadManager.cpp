//
// Created by balik on 28.06.22.
//

#include "GamepadManager.h"

namespace dualshock4 {

    void GamepadManager::gamepadSearch() {
        struct hid_device_info *cur_dev;
        cur_dev = hid_enumerate(SONY_VENDOR, 0x0);
        while (cur_dev) {
            // todo: find by BT
            if (cur_dev->product_id == SONY_DS4_USB || cur_dev->product_id == SONY_DS4_V2_USB) {
                curGamepad.HidHandle = hid_open(cur_dev->vendor_id, cur_dev->product_id, cur_dev->serial_number);
                assert(curGamepad.HidHandle != nullptr && "Failed to open HID!");
                hid_set_nonblocking(curGamepad.HidHandle, 1);
                curGamepad.ControllerType = SONY_DUALSHOCK4;
                curGamepad.USBConnection = true;
                break;
            }
            cur_dev = cur_dev->next;
        }
        if (cur_dev) {
            hid_free_enumeration(cur_dev);
        }

        assert(curGamepad.HidHandle != nullptr);
    }

    void GamepadManager::gamepadSetState(internal::LedState OutState) {
        assert(curGamepad.HidHandle != nullptr);

        if (curGamepad.ControllerType == SONY_DUALSHOCK4 && curGamepad.USBConnection) {
            unsigned char outputReport[31];
            memset(outputReport, 0, 31);

            outputReport[0] = 0x05;
            outputReport[1] = 0xff;
            outputReport[4] = 0; //OutState.SmallMotor;
            outputReport[5] = 0; //OutState.LargeMotor;
            outputReport[6] = std::clamp(OutState.LEDRed - OutState.LEDBrightness, 0, 255);
            outputReport[7] = std::clamp(OutState.LEDGreen - OutState.LEDBrightness, 0, 255);
            outputReport[8] = std::clamp(OutState.LEDBlue - OutState.LEDBrightness, 0, 255);

            hid_write(curGamepad.HidHandle, outputReport, 31);
        } // todo: BT
    }
}