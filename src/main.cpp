#include <iostream>

#include "external/lib/Additional.h"
#include "external/lib/CommandManager.h"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cout << "Please pass path to project directory or special command (--help for more information)." << std::endl;
        return 0;
    }

    FileManager manager;
    CommandManager cmdManager;

    std::string argument(argv[1]);
    if (cmdManager.hasCommand(argc, argv) == true)
    {
        cmdManager.parseCommand(argc, argv);
        return 0;
    }

    replace(argument, "ampi.exe", "");
    manager.setPath(argument);

    if (manager.hasConfigFile())
    {
        if (!manager.readConfigFile())
        {
            return 0;
        }
        // Run interpreter or compiler.
    }
    else
        std::cout << "Config file doesn't exists." << std::endl;

    return 0;
};