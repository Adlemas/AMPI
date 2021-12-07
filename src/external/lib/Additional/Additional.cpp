#include "../Additional.h"

bool replace(std::string &str, const std::string &from, const std::string &to)
{
    size_t start_pos = str.find(from);
    if (start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
};

std::vector<std::string> split(std::string str, std::string delimiter)
{
    std::vector<std::string> tokens;

    size_t pos = 0;
    std::string token;
    while ((pos = str.find(delimiter)) != std::string::npos)
    {
        token = str.substr(0, pos);
        tokens.push_back(token);
        str.erase(0, pos + delimiter.length());
    }

    return tokens;
};

char *push(char *str, char a)
{
    size_t len = strlen(str);
    char *ret = new char[len + 2];

    strcpy(ret, str);
    ret[len] = a;
    ret[len + 1] = '\0';

    return ret;
}