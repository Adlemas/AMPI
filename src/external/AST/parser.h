#ifndef AMPI_PARSER_H
#define AMPI_PARSER_H

#include "tokenizer.h"

enum _Statements
{
    BINARY,
    VARIABLE_DECLARATION,
};
typedef enum _Statements Statements;

enum _VarDeclarationTypes
{
    JUST_DECLARE,
    WITH_VALUE
};
typedef enum _VarDeclarationTypes VarDeclarationTypes;

enum _VarType
{
    CONSTANT,
    NORMAL
};
typedef enum _VarType VarType;

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
    int type;
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

struct _VariableDeclaration
{
    char *name = (char *)"";
    int type;
    int value;
};
typedef struct _VariableDeclaration VariableDeclaration;

struct _ParseStatement
{
    int type;
    VariableDeclaration *var_declare;
};
typedef struct _ParseStatement ParseStatement;

struct _ParseTree
{
    Variable **variables;
    int vsize = 0;
    int vptr = 0;

    ParseStatement **statements;
    int size = 0;
    int ptr = 0;

    int pos = 0;
    Token *currentToken;

    bool eat(TokenType type, TokenList *list);
    bool variable_declaration(_ParseTree *tree, TokenList *list);

    void tree_create(_ParseTree *tree, int size);
    void tree_statement_add(_ParseTree *tree, ParseStatement *item);
    ParserStatus tree_start(_ParseTree *tree, TokenList *list);

    void tree_var_add(_ParseTree *tree, Variable *item);
    int tree_var_exists(_ParseTree *tree, char *name);
    int tree_get_var_value(_ParseTree *tree, int index);
};
typedef struct _ParseTree ParseTree;

void binary_destroy(Binary *binary);
void parsetree_destroy(ParseTree *parsetree);

#endif