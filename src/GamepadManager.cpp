//
// Created by balik on 28.06.22.
//

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

    void GamepadManager::updateButtonState() {
        assert(curGamepad.HidHandle != nullptr);
        unsigned char packet[64];
        memset(packet, 0, 64);
        int res = hid_read_timeout(curGamepad.HidHandle, packet, 64, 1000);
        assert(res != 0); // todo: handle failures later

        if (packet[0] == 0) {
            return; // no updates
        }

#ifdef DEBUG_MODE
        printf("%02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x\n\n",
               packet[0], packet[1], packet[2], packet[3], packet[4], packet[5], packet[6], packet[7], packet[8],
               packet[9],
               packet[10], packet[11], packet[12], packet[13], packet[14], packet[15], packet[16], packet[17],
               packet[18], packet[19], packet[20],
               packet[21], packet[22], packet[23], packet[24], packet[25], packet[26], packet[27], packet[28],
               packet[29], packet[30],
               packet[31], packet[32], packet[33], packet[34], packet[35], packet[36], packet[37], packet[38],
               packet[39], packet[40],
               packet[41], packet[42], packet[43], packet[44], packet[45], packet[46], packet[47], packet[48],
               packet[49], packet[50]);
#endif
    }
}