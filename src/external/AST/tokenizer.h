#include "token.h"
#include <iostream>
#include <string>

class Tokenizer
{
    Token *token_create(int type, int data, int line, int symbol);

    void token_list_create(TokenList *list, int size);

    void token_list_add(TokenList *list, Token *tok);

    Token *token_list_get(TokenList *list, int index);

    std::string tokenizer_get_number(std::string *source, int index);

    int tokenizer_get_operator(char symbol);

public:
    void tokenize(TokenList *list, std::string source);
};