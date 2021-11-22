#include "../TimeoutManager.h"

unsigned int TimeoutManager::Timeout::getDuration()
{
    return this->duration;
};

void TimeoutManager::Timeout::setDuration(unsigned int duration)
{
    this->duration = duration;
};

void TimeoutManager::Timeout::start()
{
    Sleep(this->duration);
    this->callback(this->duration);
};

void TimeoutManager::Timeout::setInvoke(void (*invoke)(unsigned int duration))
{
    this->callback = *invoke;
};

std::function<void(unsigned int duration)> TimeoutManager::Timeout::getInvoke()
{
    return this->callback;
};

void TimeoutManager::addTimeout(unsigned int duration, void (*invoke)(unsigned int duration))
{
    Timeout timeout;
    timeout.setDuration(duration);
    timeout.setInvoke(invoke);
    this->timeouts.push_back(timeout);
};

void TimeoutManager::launch()
{
    std::sort(timeouts.begin(), timeouts.end(), compare);

    std::cout << "Sorted:" << std::endl;
    for (int i = 0; i < timeouts.size(); i++)
    {
        std::cout << "  Timeout: " << timeouts[i].getDuration() << std::endl;
    }

    unsigned int millis = 0;

    for (int i = 0; i < timeouts.size(); i++)
    {
        Sleep(timeouts[i].getDuration() - millis);
        timeouts[i].getInvoke()(timeouts[i].getDuration());
        millis = timeouts[i].getDuration();
    }
};