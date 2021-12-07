#ifndef AMPI_PARSER_H
#define AMPI_PARSER_H

#include "tokenizer.h"

enum _ParserStatus
{
    PARSER_SUCCESS,
    PARSER_ERROR
};
typedef enum _ParserStatus ParserStatus;

struct _Variable
{
    char *name = (char *)"";
    int value = 0;
};
typedef struct _Variable Variable;

struct _Binary
{
    int *data;
    int size = 0;
    int ptr = 0;

    int *types;
    int tsize = 0;
    int tptr = 0;

    Variable **variables;
    int vsize = 0;
    int vptr = 0;

    int binary_view_mul_div(_Binary *binary, TokenList *list, int index);
    void binary_create(_Binary *binary, int size);
    void binary_list_add(_Binary *binary, int item);
    void binary_type_add(_Binary *binary, int item);
    void binary_var_add(_Binary *binary, Variable *item);
    int binary_var_exists(_Binary *binary, char *name);
    int binary_get_var_value(_Binary *binary, int index);
    ParserStatus binary_start(_Binary *binary, TokenList *list);
};
typedef struct _Binary Binary;

void binary_destroy(Binary *binary);

#endif