//
// Created by balik on 28.06.22.
//

#include <cstdint>
#include <bitset>
#include <iostream>
#include "GamepadManager.h"

#define DEBUG_MODE

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

    ButtonState GamepadManager::updateButtonState() {
        assert(curGamepad.HidHandle != nullptr);
        unsigned char buf[64];
        memset(buf, 0, 64);
        int res = hid_read_timeout(curGamepad.HidHandle, buf, 64, 1000);
        assert(res != 0); // todo: handle failures later

        ButtonState result{};

        if (buf[0] == 0) {
            return result; // no updates
        }

        bool isValid = true;
        if (!curGamepad.USBConnection) {
            // todo:
        } else {
            isValid = buf[0] == 0x01;
            // todo: ignore packets from Dongle with no connected controller
        }

        if (isValid) {
            //  based on https://gist.github.com/johndrinkwater/7708901
            result.up = buf[5] == 0 || buf[5] == 1 || buf[5] == 7;
            result.right = buf[5] == 1 || buf[5] == 2 || buf[5] == 3;
            result.down = buf[5] == 3 || buf[5] == 4 || buf[5] == 5;
            result.left = buf[5] == 5 || buf[5] == 6 || buf[5] == 7;


            result.south = (buf[5] & 32) != 0;
            result.east = (buf[5] & 64) != 0;
            result.west = (buf[5] & 16) != 0;
            result.north = (buf[5] & 128) != 0;
        }

        return result;
    }
}