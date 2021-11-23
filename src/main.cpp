#include <iostream>

#include "external/lib/FileManager.h"
#include "external/lib/Additional.h"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cout << "Please pass path to project directory." << std::endl;
        return 0;
    }

    FileManager manager;

    std::string path(argv[1]);
    replace(path, "ampi.exe", "");
    manager.setPath(path);

    if (manager.hasConfigFile())
        manager.readConfigFile();
    else
        std::cout << "Config file doesn't exists." << std::endl;

    return 0;
};