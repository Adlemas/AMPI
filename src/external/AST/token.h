#ifndef AMPI_TOKEN_H
#define AMPI_TOKEN_H

#include <stdlib.h>

enum _TokenType
{
    OPERATOR,
    NUMBER,
    ID,
    OPEN_ROUND_BRACKET,
    CLOSE_ROUND_BRACKET,
    VARIABLE_KEYWORD,
    IF_KEYWORD,
    ELSE_KEYWORD,
    FUNCTION_KEYWORD,
    SEMICOLON,
    EQUAL,
    UNDEFINED
};
typedef enum _TokenType TokenType;

enum _TokenOperator
{
    PLUS,
    MINUS,
    DIVIDE,
    MUL
};
typedef enum _TokenOperator TokenOperator;

struct _Token
{
    int type;
    int data;
    int line;
    int symbol;
    char *value;
};
typedef struct _Token Token;

struct _TokenList
{
    Token **data = {};
    int ptr = 0;
    int size = 0;

    Token *getToken(_TokenList *list, int pos);
};
typedef struct _TokenList TokenList;

void token_list_destroy(TokenList *list);

#endif