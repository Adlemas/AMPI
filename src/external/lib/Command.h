#include <vector>
#include <string>

#include "Additional.h"

class Command
{
private:
    std::string workingFolder;

    std::string command;
    std::string attribute;
    std::string line;

    std::vector<std::string> cmds = {
        "init",
        "build"};

    std::vector<std::string> attributes = {
        "--help",
        "-c",
        "-i"};

    void setLine(std::string line);
    void setCommand(std::string command);
    void setAttribute(std::string attribute);

    bool isCommand(std::string argument);

public:
    bool hasCommand(int argc, char **argv);

    bool parseCommand(std::vector<std::string> args);
};