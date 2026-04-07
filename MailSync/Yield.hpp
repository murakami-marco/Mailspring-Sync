#pragma once
#include <chrono>
#include <thread>

/**
 * Utility class to prevent CPU graduation/starvation in tight loops.
 * Call `sleepIfBusy()` inside long-running loops to ensure the thread
 * periodically yields control back to the OS and other threads.
 */
class Yield {
public:
    Yield(int workDurationMs = 250, int sleepDurationMs = 50)
        : _workDurationMs(workDurationMs), _sleepDurationMs(sleepDurationMs) {
        _lastSleepTime = std::chrono::steady_clock::now();
    }

    void sleepIfBusy() {
        auto currentTime = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - _lastSleepTime).count() > _workDurationMs) {
            std::this_thread::sleep_for(std::chrono::milliseconds(_sleepDurationMs));
            _lastSleepTime = std::chrono::steady_clock::now();
        }
    }

private:
    int _workDurationMs;
    int _sleepDurationMs;
    std::chrono::steady_clock::time_point _lastSleepTime;
};
