#include <vector>
#include <string>

#include "Additional.h"
#include "FileManager.h"

class CommandManager
{
private:
    FileManager __fileManager;

    std::string workingFolder;

    std::string command;
    std::string attribute;

    std::vector<std::string> parameters;

    int argc = 0;

    std::vector<std::string> cmds = {
        "init",
        "build"};

    std::vector<std::string> attributes = {
        "--help",
        "-c",
        "-i"};

    void setCommand(std::string command);
    void setAttribute(std::string attribute);

    bool isCommand(std::string argument);

    bool init(std::string attribute, std::vector<std::string> parameters);

    bool run(std::string attribute, std::vector<std::string> parameters);

public:
    void setFileManager(FileManager fileManager);

    bool hasCommand(int argc, char **argv);

    bool parseCommand(int argc, char **argv);
};