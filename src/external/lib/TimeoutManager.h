#include <windows.h>
#include <vector>
#include <bits/stdc++.h>
#include <algorithm>

class TimeoutManager
{
private:
    class Timeout
    {
    private:
        unsigned int duration = 0;

        void (*callback)(unsigned int duration);

    public:
        void setDuration(unsigned int duration);
        void setInvoke(void (*invoke)(unsigned int duration));

        unsigned int getDuration();
        std::function<void(unsigned int duration)> getInvoke();

        void start();
    };

    struct
    {
        bool operator()(Timeout timeout1, Timeout timeout2)
        {
            return (timeout1.getDuration() < timeout2.getDuration());
        }
    } compare;

    std::vector<Timeout> timeouts;

public:
    void addTimeout(unsigned int duration, void (*invoke)(unsigned int duration));

    void launch();
};