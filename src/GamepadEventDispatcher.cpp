//
// Created by balik on 28.06.22.
//

#include "GamepadEventDispatcher.h"

namespace dualshock4 {

    void GamepadEventDispatcher::registerEventHandler(KeyEvent event, const std::function<void()>& handler) {
        dispatcher.appendListener(event, handler);
    }

    void GamepadEventDispatcher::runEventLoop() {
        while (isRunning.load()) {
            // todo:
            dispatcher.dispatch(KEY_SOUTH);
        }
    }
}