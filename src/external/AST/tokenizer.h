#include "token.h"
#include <iostream>
#include <string>
#include <bits/stdc++.h>

class Tokenizer
{
    Token *token_create(int type, int data, int line, int symbol, char *value);

    void token_list_create(TokenList *list, int size);

    void token_list_add(TokenList *list, Token *tok);

    Token *token_list_get(TokenList *list, int index);

    char *append(char *array, char a);

    char *tokenizer_get_number(std::string *source, int index);
    char *tokenizer_get_id(std::string *source, int index);

    int tokenizer_get_operator(char symbol);

public:
    void tokenize(TokenList *list, std::string source);
};