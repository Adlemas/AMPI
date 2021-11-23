#include <string>

class AST
{
private:
    std::string __code;

public:
    void setText(std::string text);
    void ParseAST();
};