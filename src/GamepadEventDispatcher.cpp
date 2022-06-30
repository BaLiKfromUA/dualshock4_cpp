//
// Created by balik on 28.06.22.
//

#include "GamepadEventDispatcher.h"
#include "GamepadManager.h"

#define DELAY 200

namespace dualshock4 {

    void GamepadEventDispatcher::registerEventHandler(KeyEvent event, const std::function<void()> &handler) {
        dispatcher.appendListener(event, handler);
    }

    void GamepadEventDispatcher::runEventLoop() {
        GamepadManager manager;

        manager.gamepadSearch();
        manager.setReadyColor();

        while (isRunning.load()) {
            auto buttonState = manager.updateButtonState();

            if (buttonState.up) {
                dispatcher.dispatch(KeyEvent::KEY_UP);
            }

            if (buttonState.down) {
                dispatcher.dispatch(KeyEvent::KEY_DOWN);
            }

            if (buttonState.left) {
                dispatcher.dispatch(KeyEvent::KEY_LEFT);
            }

            if (buttonState.right) {
                dispatcher.dispatch(KeyEvent::KEY_RIGHT);
            }

            if (buttonState.north) {
                dispatcher.dispatch(KeyEvent::KEY_NORTH);
            }

            if (buttonState.south) {
                dispatcher.dispatch(KeyEvent::KEY_SOUTH);
            }

            if (buttonState.west) {
                dispatcher.dispatch(KeyEvent::KEY_WEST);
            }

            if (buttonState.east) {
                dispatcher.dispatch(KeyEvent::KEY_EAST);
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
        }
    }
}