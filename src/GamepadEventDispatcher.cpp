//
// Created by balik on 28.06.22.
//

#include "GamepadEventDispatcher.h"
#include "GamepadManager.h"

#define DELAY 1000

namespace dualshock4 {

    void GamepadEventDispatcher::registerEventHandler(KeyEvent event, const std::function<void()> &handler) {
        dispatcher.appendListener(event, handler);
    }

    void GamepadEventDispatcher::runEventLoop() {
        GamepadManager manager;
        manager.gamepadSearch();

        while (isRunning.load()) {
            manager.updateButtonState();
            std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
        }
    }
}