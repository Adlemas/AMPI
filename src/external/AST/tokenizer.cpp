#include "tokenizer.h"

#define variable_keyword "v"
#define function_keyword "f"
#define if_keyword "if"
#define else_keyword "else"

Token *Tokenizer::token_create(int type, int data, int line, int symbol, char *value)
{
    Token *tok = (Token *)std::malloc(sizeof(Token));
    tok->type = type;
    tok->data = data;
    tok->line = line;
    tok->symbol = symbol;
    tok->value = value;
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

char *Tokenizer::tokenizer_get_number(std::string *source, int index)
{
    std::string num_str = "";
    num_str += (*source)[index++];
    while ((*source)[index] == '1' || (*source)[index] == '2' || (*source)[index] == '3' || (*source)[index] == '4' || (*source)[index] == '5' || (*source)[index] == '6' || (*source)[index] == '7' || (*source)[index] == '8' || (*source)[index] == '9' || (*source)[index] == '0')
    {
        num_str += (*source)[index++];
    }
    return (char *)num_str.c_str();
};

char *Tokenizer::append(char *array, char a)
{
    size_t len = strlen(array);
    char *ret = new char[len + 2];

    strcpy(ret, array);
    ret[len] = a;
    ret[len + 1] = '\0';

    return ret;
}

char *Tokenizer::tokenizer_get_id(std::string *source, int index)
{
    char *id = (char *)"";
    id = append(id, (*source)[index++]);
    while (std::isalpha((*source)[index]) || std::isdigit((*source)[index]))
    {
        id = append(id, (*source)[index++]);
    }
    return id;
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

TokenizeStatus Tokenizer::tokenize(TokenList *list, std::string source)
{
    int line = 1;
    int symbol = 1;

    for (int i = 0; i < source.length(); i++)
    {
        if (source[i] == '1' || source[i] == '2' || source[i] == '3' || source[i] == '4' || source[i] == '5' || source[i] == '6' || source[i] == '7' || source[i] == '8' || source[i] == '9' || source[i] == '0')
        {
            std::string number = tokenizer_get_number(&source, i);
            token_list_add(list, token_create(NUMBER, std::stoi(number), line, symbol, (char *)""));
            i += number.length() - 1;
        }
        else if (source[i] == '+' || source[i] == '-' || source[i] == '*' || source[i] == '/')
        {
            int op = tokenizer_get_operator(source[i]);
            token_list_add(list, token_create(OPERATOR, op, line, symbol, (char *)""));
        }
        else if (std::isalpha(source[i]))
        {
            char *id = tokenizer_get_id(&source, i);

            std::cout << std::endl;

            if (strcmp(id, variable_keyword) == 0)
            {
                token_list_add(list, token_create(VARIABLE_KEYWORD, 0, line, symbol, (char *)""));
            }
            else if (strcmp(id, if_keyword) == 0)
            {
                token_list_add(list, token_create(IF_KEYWORD, 0, line, symbol, (char *)""));
            }
            else if (strcmp(id, else_keyword) == 0)
            {
                token_list_add(list, token_create(ELSE_KEYWORD, 0, line, symbol, (char *)""));
            }
            else if (strcmp(id, function_keyword) == 0)
            {
                token_list_add(list, token_create(FUNCTION_KEYWORD, 0, line, symbol, (char *)""));
            }
            else
            {
                token_list_add(list, token_create(ID, 0, line, symbol, id));
            }

            i += strlen(id) - 1;
        }
        else if (source[i] == '\n')
        {
            line++;
            symbol = 0;
        }
        else if (source[i] == '=')
        {
            token_list_add(list, token_create(EQUAL, 0, line, symbol, (char *)""));
        }
        else if (source[i] == ';')
        {
            token_list_add(list, token_create(SEMICOLON, 0, line, symbol, (char *)""));
        }
        else if (source[i] != ' ' && source[i] != '\0' && source[i] != '\r')
        {
            std::cout << "FatalError: undefined token at " << line << ':' << symbol << '.' << std::endl;
            return TOKENIZE_ERROR;
        }
        symbol++;
    };

    return TOKENIZE_SUCCESS;
};