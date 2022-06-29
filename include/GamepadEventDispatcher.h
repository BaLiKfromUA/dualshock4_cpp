//
// Created by balik on 28.06.22.
//

#ifndef DUALSHOCK4_CPP_GAMEPADEVENTDISPATCHER_H
#define DUALSHOCK4_CPP_GAMEPADEVENTDISPATCHER_H

#include <thread>
#include "eventpp/eventdispatcher.h"

namespace dualshock4 {

    enum KeyEvent {
        KEY_UP,
        KEY_DOWN,
        KEY_LEFT,
        KEY_RIGHT,
        KEY_NORTH, // △
        KEY_SOUTH, // ✕
        KEY_WEST, // □
        KEY_EAST // ○
    };

    class GamepadEventDispatcher {
    private:
        eventpp::EventDispatcher<KeyEvent, void()> dispatcher{};
        std::atomic<bool> isRunning = false;
        std::thread *eventLoopThread = nullptr;

        void runEventLoop();

    public:
        ~GamepadEventDispatcher() {
            stop();
            wait();
            operator delete(eventLoopThread);
        }

        void registerEventHandler(KeyEvent event, const std::function<void()> &handler);

        void start() {
            if (!isRunning.load()) {
                isRunning.store(true);
                eventLoopThread = new std::thread([this] { runEventLoop(); });
            }
        }

        void stop() {
            isRunning.store(false);
        }

        void wait() {
            assert(eventLoopThread != nullptr && eventLoopThread->joinable());
            eventLoopThread->join();
        }
    };

}


#endif //DUALSHOCK4_CPP_GAMEPADEVENTDISPATCHER_H
