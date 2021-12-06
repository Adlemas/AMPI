#include "tokenizer.h"

#define variable_keyword "v"
#define function_keyword "f"
#define if_keyword "if"
#define else_keyword "else"

Token *Tokenizer::token_create(int type, int data, int line, int symbol)
{
    Token *tok = (Token *)std::malloc(sizeof(Token));
    tok->type = type;
    tok->data = data;
    tok->line = line;
    tok->symbol = symbol;
    return tok;
};

void Tokenizer::token_list_create(TokenList *list, int size)
{
    list->data = (Token **)std::malloc(sizeof(Token *) * size);
    list->ptr = 0;
    list->size = size;
};

void Tokenizer::token_list_add(TokenList *list, Token *tok)
{
    if (list->ptr >= list->size)
    {
        list->size = list->size * 2 + 1;
        list->data = (Token **)std::realloc(list->data, sizeof(Token *) * list->size);
    }

    list->data[list->ptr++] = tok;
};

Token *Tokenizer::token_list_get(TokenList *list, int index)
{
    return list->data[index];
};

std::string Tokenizer::tokenizer_get_number(std::string *source, int index)
{
    std::string num_str = "";
    num_str += (*source)[index++];
    while ((*source)[index] == '1' || (*source)[index] == '2' || (*source)[index] == '3' || (*source)[index] == '4' || (*source)[index] == '5' || (*source)[index] == '6' || (*source)[index] == '7' || (*source)[index] == '8' || (*source)[index] == '9' || (*source)[index] == '0')
    {
        num_str += (*source)[index++];
    }
    return num_str;
};

int Tokenizer::tokenizer_get_operator(char symbol)
{
    if (symbol == '+')
        return PLUS;
    else if (symbol == '-')
        return MINUS;
    else if (symbol == '/')
        return DIVIDE;
    else if (symbol == '*')
        return MUL;
    else
        return -1;
};

void Tokenizer::tokenize(TokenList *list, std::string source)
{
    int line = 1;
    int symbol = 1;

    for (int i = 0; i < source.length(); i++)
    {
        if (source[i] == '1' || source[i] == '2' || source[i] == '3' || source[i] == '4' || source[i] == '5' || source[i] == '6' || source[i] == '7' || source[i] == '8' || source[i] == '9' || source[i] == '0')
        {
            std::string number = tokenizer_get_number(&source, i);
            token_list_add(list, token_create(NUMBER, std::stoi(number), line, symbol));
            i += number.length() - 1;
        }
        else if (source[i] == '+' || source[i] == '-' || source[i] == '*' || source[i] == '/')
        {
            int op = tokenizer_get_operator(source[i]);
            std::cout << "adding operator: " << op << std::endl;
            token_list_add(list, token_create(OPERATOR, op, line, symbol));
            std::cout << "added operator!" << std::endl;
        }
        else if (source[i] == '\n')
        {
            std::cout << "   It's new line." << std::endl;
            line++;
            symbol = 0;
        }
        symbol++;
    };
};