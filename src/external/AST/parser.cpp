#include "parser.h"

void parsetree_destroy(ParseTree *parsetree)
{
    for (int i = 0; i < parsetree->vptr; i++)
    {
        std::free(parsetree->variables[i]);
    }
    for (int i = 0; i < parsetree->ptr; i++)
    {
        std::free(parsetree->statements[i]->var_declare);
        std::free(parsetree->statements[i]);
    }
    std::free(parsetree->variables);
    std::free(parsetree->statements);
    std::free(parsetree);
};

VariableDeclaration *vardeclare_create(char *name, int type, int value)
{
    VariableDeclaration *vardeclare = (VariableDeclaration *)std::malloc(sizeof(VariableDeclaration));
    vardeclare->name = name;
    vardeclare->type = type;
    vardeclare->value = value;
    return vardeclare;
};

ParseStatement *statement_create(int type, VariableDeclaration *vardeclare)
{
    ParseStatement *statement = (ParseStatement *)std::malloc(sizeof(ParseStatement));
    statement->type = type;
    statement->var_declare = vardeclare;
    return statement;
};

void ParseTree::tree_create(ParseTree *tree, int size)
{
    tree->variables = (Variable **)std::malloc(sizeof(Variable *) * size);
    tree->vptr = 0;
    tree->vsize = size;

    tree->statements = (ParseStatement **)std::malloc(sizeof(ParseStatement *) * size);
    tree->size = 0;
    tree->ptr = 0;

    tree->pos = 0;

    tree->currentToken = (Token *)std::malloc(sizeof(Token *));
};

void ParseTree::tree_var_add(ParseTree *tree, Variable *item)
{
    if (tree->vptr >= tree->vsize)
    {
        tree->vsize = tree->vsize * 2 + 1;
        tree->variables = (Variable **)std::realloc(tree->variables, sizeof(Variable *) * tree->vsize);
    }

    tree->variables[tree->vptr++] = item;
};

int ParseTree::tree_var_exists(_ParseTree *tree, char *name)
{
    for (int i = 0; i < tree->vptr; i++)
    {
        if (strcmp(tree->variables[i]->name, name) == 0)
        {
            return i;
        }
    }
    return -1;
};

void ParseTree::tree_statement_add(ParseTree *tree, ParseStatement *item)
{
    if (tree->ptr >= tree->size)
    {
        tree->size = tree->size * 2 + 1;
        tree->statements = (ParseStatement **)std::realloc(tree->statements, sizeof(ParseStatement *) * tree->size);
    }

    tree->statements[tree->ptr++] = item;
}

bool ParseTree::eat(TokenType type, TokenList *list)
{
    if (currentToken->type != type)
    {
        std::cout << "ParseError: unexpected token at " << currentToken->line << ':' << currentToken->symbol << '!' << std::endl;
        return false;
    }
    else
    {
        pos++;
        currentToken = list->getToken(list, pos);
        return true;
    }
}

bool ParseTree::variable_declaration(_ParseTree *tree, TokenList *list)
{
    if (!tree->eat(VARIABLE_KEYWORD, list))
        return false;

    int type = -1;

    char *name = tree->currentToken->value;
    if (!tree->eat(ID, list))
        return false;

    if (tree->currentToken->type == SEMICOLON)
    {
        tree->tree_statement_add(tree, statement_create(VARIABLE_DECLARATION, vardeclare_create(name, JUST_DECLARE, 0)));
    }
    else
    {
        if (!tree->eat(EQUAL, list))
            return false;
        int value = tree->currentToken->data;
        if (!tree->eat(NUMBER, list))
            return false;
        if (!tree->eat(SEMICOLON, list))
            return false;
        tree->tree_statement_add(tree, statement_create(VARIABLE_DECLARATION, vardeclare_create(name, WITH_VALUE, value)));
    }

    return true;
};

ParserStatus ParseTree::tree_start(ParseTree *tree, TokenList *list)
{
    tree->currentToken = list->data[0];

    while (tree->currentToken->type != UNDEFINED)
    {
        if (tree->currentToken->type == VARIABLE_KEYWORD)
        {
            if (!variable_declaration(tree, list))
                return PARSER_ERROR;
        }
        else
        {
            std::cout << "ParseError: unexpected token at " << tree->currentToken->line << ':' << tree->currentToken->symbol << '.' << std::endl;
            return PARSER_ERROR;
        }
    };

    std::cout << "Statements: " << tree->ptr << std::endl;

    return PARSER_SUCCESS;
};

int ParseTree::tree_get_var_value(_ParseTree *tree, int index)
{
    return tree->variables[index]->value;
};

Variable *variable_create(char *name, int value, int type)
{
    Variable *var = (Variable *)std::malloc(sizeof(Variable));
    var->name = name;
    var->value = value;
    var->type = type;
    return var;
};

void Binary::binary_create(Binary *binary, int size)
{
    binary->data = (int *)std::malloc(sizeof(int) * size);
    binary->ptr = 0;
    binary->size = size;

    binary->types = (int *)std::malloc(sizeof(int) * size);
    binary->tptr = 0;
    binary->tsize = size;

    binary->variables = (Variable **)std::malloc(sizeof(Variable *) * size);
    binary->vptr = 0;
    binary->vsize = size;
};

void binary_destroy(Binary *binary)
{
    std::free(binary->data);
    std::free(binary->types);

    for (int i = 0; i < binary->vptr; i++)
    {
        std::free(binary->variables[i]);
    }

    std::free(binary->variables);
    std::free(binary);
};

void Binary::binary_list_add(_Binary *binary, int item)
{
    if (binary->ptr >= binary->size)
    {
        binary->size = binary->size * 2 + 1;
        binary->data = (int *)std::realloc(binary->data, sizeof(int) * binary->size);
    }

    binary->data[binary->ptr++] = item;
}

void Binary::binary_type_add(_Binary *binary, int item)
{
    if (binary->tptr >= binary->tsize)
    {
        binary->tsize = binary->tsize * 2 + 1;
        binary->types = (int *)std::realloc(binary->types, sizeof(int) * binary->tsize);
    }

    binary->types[binary->tptr++] = item;
}

void Binary::binary_var_add(_Binary *binary, Variable *item)
{
    if (binary->vptr >= binary->vsize)
    {
        binary->vsize = binary->vsize * 2 + 1;
        binary->variables = (Variable **)std::realloc(binary->variables, sizeof(Variable *) * binary->vsize);
    }

    binary->variables[binary->vptr++] = item;
}

int Binary::binary_var_exists(_Binary *binary, char *name)
{
    for (int i = 0; i < binary->vptr; i++)
    {
        if (strcmp(binary->variables[i]->name, name) == 0)
        {
            return i;
        }
    }
    return -1;
}

int Binary::binary_get_var_value(_Binary *binary, int index)
{
    return binary->variables[index]->value;
}

ParserStatus Binary::binary_start(Binary *binary, TokenList *list)
{
    for (int i = 0; i < list->ptr; i++)
    {
        Token *tok = list->data[i];
        if (tok->type == NUMBER)
        {
            if (i != (list->ptr - 1) && list->data[i + 1]->type == OPERATOR && (list->data[i + 1]->data == MUL || list->data[i + 1]->data == DIVIDE))
            {
                int status = binary_view_mul_div(binary, list, i);
                if (status < 0)
                    return PARSER_ERROR;
                else
                    i = status - 1;
            }
            else
            {
                binary_list_add(binary, tok->data);
                binary_type_add(binary, NUMBER);
            }
        }
        else if (tok->type == OPERATOR)
        {
            binary_list_add(binary, tok->data);
            binary_type_add(binary, OPERATOR);
        }
        else if (tok->type == ID)
        {
            if (binary_var_exists(binary, tok->value) > -1)
            {
                int index = binary_var_exists(binary, tok->value);
                binary_list_add(binary, binary_get_var_value(binary, index));
                binary_type_add(binary, NUMBER);
            }
            else
            {
                std::cout << "  ParseError: undefined variable at " << tok->line << ':' << tok->symbol << '.' << std::endl;
                return PARSER_ERROR;
            }
        }
        else
        {
            std::cout << "  ParseError: unexpected token at " << tok->line << ':' << tok->symbol << '.';
            return PARSER_ERROR;
        }
    }

    std::cout << "\n";

    return PARSER_SUCCESS;
};

int Binary::binary_view_mul_div(_Binary *binary, TokenList *list, int index)
{
    int start = index;
    int result = 0;
    while (list->ptr > index && ((list->data[index]->type == OPERATOR && list->data[index]->data == MUL || list->data[index]->data == DIVIDE) || list->data[index]->type == NUMBER))
    {
        if (list->data[index]->type == OPERATOR)
        {
            if (list->data[index]->data == MUL)
            {
                if (list->data[index + 1]->type == NUMBER)
                {
                    result *= list->data[index + 1]->data;
                    index++;
                }
                else if (list->data[index + 1]->type == ID)
                {
                    if (binary_var_exists(binary, list->data[index + 1]->value) > -1)
                        result *= binary_get_var_value(binary, binary_var_exists(binary, list->data[index + 1]->value));
                    else
                    {
                        std::cout << "  ParseError: undefined variable at " << list->data[index + 1]->line << ':' << list->data[index + 1]->symbol << '.' << std::endl;
                        return -1;
                    }
                }
                else
                {
                    std::cout << "Unexpected token at " << list->data[index + 1]->line << ':' << list->data[index + 1]->symbol << std::endl;
                    return -1;
                }
            }
            else if (list->data[index]->data == DIVIDE)
            {
                if (list->data[index + 1]->type == NUMBER)
                {
                    result /= list->data[index + 1]->data;
                    index++;
                }
                else if (list->data[index + 1]->type == ID)
                {
                    int index = binary_var_exists(binary, list->data[index + 1]->value);
                    if (index > -1)
                        result /= binary_get_var_value(binary, index);
                    else
                    {
                        std::cout << "  ParseError: undefined variable at " << list->data[index + 1]->line << ':' << list->data[index + 1]->symbol << '.' << std::endl;
                        return PARSER_ERROR;
                    }
                }
                else
                {
                    std::cout << "Unexpected token at " << list->data[index + 1]->line << ':' << list->data[index + 1]->symbol << std::endl;
                    return -1;
                }
            }
        }
        else if (list->data[index]->type == NUMBER)
        {
            if (index == start)
                result = (int)list->data[index]->data;
        }
        else if (list->data[index]->type == ID)
        {
            if (binary_var_exists(binary, list->data[index]->value) > -1)
            {
                int index = binary_var_exists(binary, list->data[index]->value);
                int value = binary_get_var_value(binary, index);
                if (index == start)
                    result = value;
            }
            else
            {
                std::cout << "  ParseError: undefined variable at " << list->data[index]->line << ':' << list->data[index]->symbol << '.' << std::endl;
                return PARSER_ERROR;
            }
        }

        index++;
    }

    binary_list_add(binary, result);
    binary_type_add(binary, NUMBER);

    return index;
};