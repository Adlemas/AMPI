#ifndef _WIN32
#include "windows.h"
#else
#include "unistd.h"
#endif
#include <iostream>

int main(int argc, char **argv)
{
    std::cout << "Hello" << std::endl;
    std::cout.flush();
    sleep(5);
    std::cout << " World!" << std::endl;
    return 0;
};