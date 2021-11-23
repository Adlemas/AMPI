#include "../CommandManager.h"

bool CommandManager::isCommand(std::string attribute)
{
    for (const auto &cmd : cmds)
    {
        if (attribute == cmd)
        {
            return true;
        }
    }
    return false;
};

void CommandManager::setCommand(std::string command)
{
    this->command = command;
};

void CommandManager::setAttribute(std::string attribute)
{
    this->attribute = attribute;
};

bool CommandManager::hasCommand(int argc, char **argv)
{
    for (int i = 0; i < argc; i++)
    {
        if (this->isCommand(argv[i]))
            return true;
    }
    return false;
};

bool CommandManager::parseCommand(int argc, char **argv)
{
    for (int i = 0; i < argc; i++)
    {
        bool isCommand = false;
        for (int j = 0; j < this->cmds.size(); j++)
        {
            if (this->cmds[j] == argv[i])
            {
                isCommand = true;
                this->command = argv[i];
                break;
            }
        }
        bool isAttribute = false;
        if (!isCommand)
        {
            for (int j = 0; j < this->attributes.size(); j++)
            {
                if (this->attributes[j] == argv[i])
                {
                    isAttribute = true;
                    this->attribute = argv[i];
                    break;
                }
            }
            if (!isAttribute && i != 0)
            {
                this->parameters.push_back(argv[i]);
            }
        }
    }

    if (command == "init")
    {
        return (this->init(this->attribute, this->parameters));
    }
    else if (command == "run")
    {
        return (this->run(this->attribute, this->parameters));
    }

    std::cout << "Unknown command: \"" << command << "\"!" << std::endl;
    return false;
};

bool CommandManager::init(std::string attribute, std::vector<std::string> parameters)
{
    if (attribute == "")
    {
        char tmp[256];
        getcwd(tmp, 256);
        __fileManager.setPath(tmp);
        return (__fileManager.initProject());
    }
    else
    {
        std::cout << "Unknown attribute in init command: \"" << attribute << "\"!" << std::endl;
        return false;
    }
}

void CommandManager::setFileManager(FileManager fileManager)
{
    this->__fileManager = fileManager;
};
