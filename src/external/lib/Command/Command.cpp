#include "../Command.h"

bool Command::isCommand(std::string attribute)
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

void Command::setLine(std::string line)
{
    this->line = line;
};

void Command::setCommand(std::string command)
{
    this->command = command;
};

void Command::setAttribute(std::string attribute)
{
    this->attribute = attribute;
};

bool Command::hasCommand(int argc, char **argv)
{
    for (int i = 0; i < argc; i++)
    {
        if (this->isCommand(argv[i]))
            return true;
    }
    return false;
};