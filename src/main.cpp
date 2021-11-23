#include <iostream>

#include "external/lib/FileManager.h"
#include "external/lib/Additional.h"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cout << "Please pass path to project directory or special command (--help for more information)." << std::endl;
        return 0;
    }

    FileManager manager;

    std::string argument(argv[1]);
    if (argument == "init")
    {
        char tmp[256];
        getcwd(tmp, 256);
        manager.setPath(tmp);
        manager.initProject();
        return 0;
    }

    replace(argument, "ampi.exe", "");
    manager.setPath(argument);

    if (manager.hasConfigFile())
        manager.readConfigFile();
    else
        std::cout << "Config file doesn't exists." << std::endl;

    return 0;
};