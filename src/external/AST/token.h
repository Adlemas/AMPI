#ifndef AMPI_TOKEN_H
#define AMPI_TOKEN_H

#include <stdlib.h>

enum _TokenType
{
    OPERATOR,
    NUMBER,
    ID,
    VARIABLE_KEYWORD,
    IF_KEYWORD,
    ELSE_KEYWORD,
    FUNCTION_KEYWORD
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
};
typedef struct _TokenList TokenList;

void token_list_destroy(TokenList *list);

#endif