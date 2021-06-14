#include "TimerPort.hpp"
#include <thread>

namespace ue
{

TimerPort::TimerPort(common::ILogger &logger)
    : logger(logger, "[TIMER PORT]")
{}

void TimerPort::start(ITimerEventsHandler &handler)
{
    logger.logDebug("Started");
    this->handler = &handler;
}

void TimerPort::stop()
{
    logger.logDebug("Stoped");
    handler = nullptr;
}

void TimerPort::startTimer(Duration duration)
{
    auto durationCount = duration.count();
    logger.logDebug("Start timer: ", durationCount, "ms");
    isRunning = true;
    startTime = std::chrono::system_clock::now();
    std::thread t([&, durationCount](){
        while(isRunning) {
            if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - startTime).count() > durationCount) {
                handler->handleTimeout();
                break;
            }
        }

    });
    t.detach();
}

void TimerPort::stopTimer()
{
    logger.logDebug("Stop timer");
    isRunning = false;
}

}
