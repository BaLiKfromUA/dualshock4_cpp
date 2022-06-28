//
// Created by balik on 28.06.22.
//

#include "GamepadEventDispatcher.h"
#include "GamepadManager.h"

namespace dualshock4 {

    void GamepadEventDispatcher::registerEventHandler(KeyEvent event, const std::function<void()> &handler) {
        dispatcher.appendListener(event, handler);
    }

    void GamepadEventDispatcher::runEventLoop() {
        GamepadManager manager;
        manager.gamepadSearch();

        while (isRunning.load()) {
            // todo:
            dispatcher.dispatch(KEY_SOUTH);
        }
    }
}