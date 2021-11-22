#include <iostream>

#include "external/lib/TimeoutManager.h"

void viewTimeout(unsigned int duration)
{
    std::cout << (duration) << " milliseconds timeout!" << std::endl;
};

int main(int argc, char **argv)
{
    TimeoutManager manager;

    manager.addTimeout(4 * 1000, viewTimeout);
    manager.addTimeout(5 * 1000, viewTimeout);
    manager.addTimeout(6 * 1000, viewTimeout);
    manager.addTimeout(2 * 1000, viewTimeout);
    manager.addTimeout(10 * 1000, viewTimeout);
    manager.addTimeout(8 * 1000, viewTimeout);
    manager.addTimeout(2.5 * 1000, viewTimeout);
    manager.addTimeout(3 * 1000, viewTimeout);

    manager.launch();

    return 0;
};