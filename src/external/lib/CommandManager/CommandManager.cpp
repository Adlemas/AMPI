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

    char tmp[256];
    getcwd(tmp, 256);
    __fileManager.setPath(tmp);

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

bool CommandManager::run(std::string attribute, std::vector<std::string> parameters)
{
    std::string filename = this->__fileManager.getSettings().value("index", "");
    std::string mainPath = this->__fileManager.join(this->__fileManager.getPath(), filename);
    std::ifstream f;
    f.open(mainPath.c_str(), std::ios::in | std::ios::binary);
    if (!f.is_open())
    {
        std::cerr << "Failed to open ampi file: " << mainPath << std::endl;
        return false;
    }

    std::stringstream buffer;
    buffer << f.rdbuf();

    std::string source = buffer.str();

    TokenList list;
    Tokenizer tokenizer;

    tokenizer.tokenize(&list, source);

    Binary binary;
    binary.binary_create(&binary, 1);

    ParserStatus pstat = binary.binary_start(&binary, &list);
    if (pstat == PARSER_SUCCESS)
    {
        int value = binary.data[0];
        for (int i = 1; i < binary.ptr; i++)
        {
            if (binary.types[i] == OPERATOR)
            {
                if (binary.types[i + 1] == NUMBER)
                {
                    if (binary.data[i] == PLUS)
                    {
                        value += binary.data[i + 1];
                    }
                    else if (binary.data[i] == MINUS)
                    {
                        value -= binary.data[i + 1];
                    }
                    else
                    {
                        std::cout << "ParseError: unexpected token " << binary.data[i] << '!' << std::endl;
                        return false;
                    }
                    i++;
                }
                else
                {
                    std::cout << "ParseError: unexpected token " << binary.data[i + 1] << '!' << std::endl;
                    return false;
                }
            }
            else
            {
                std::cout << "ParseError: unexpected token " << binary.data[i] << '!' << std::endl;
                return false;
            }
        }
        std::cout << "  Binary result: " << value << std::endl;
        std::cout << std::endl;
    }
    else
    {
        return false;
    }

    binary_destroy(&binary);

    token_list_destroy(&list);

    return true;
};

void CommandManager::setFileManager(FileManager fileManager)
{
    this->__fileManager = fileManager;
};
