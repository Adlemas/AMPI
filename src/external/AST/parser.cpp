#include "parser.h"

void Binary::binary_create(Binary *binary, int size)
{
    binary->data = (int *)std::malloc(sizeof(int) * size);
    binary->ptr = 0;
    binary->size = size;

    binary->types = (int *)std::malloc(sizeof(int) * size);
    binary->ptr = 0;
    binary->size = size;
};

ParserStatus Binary::binary_start(Binary *binary, TokenList *list)
{
    std::cout << "Binary start: " << list->ptr << std::endl;
    for (int i = 0; i < list->ptr; i++)
    {
        std::cout << i << std::endl;
        Token *tok = list->data[i];
        if (tok->type == NUMBER)
        {
            if (i != (list->ptr - 1) && list->data[i + 1]->type == OPERATOR && (list->data[i + 1]->data == MUL || list->data[i + 1]->data == DIVIDE))
            {
                std::cout << "It's multiply!" << std::endl;
                int status = binary_view_mul_div(binary, list, i);
                if (status < 0)
                    return PARSER_ERROR;
                else
                    i = status - 1;
            }
            else
            {
                std::cout << "It's binary!" << std::endl;
                binary_list_add(binary, tok->data);
                binary_type_add(binary, NUMBER);
            }
        }
        else if (tok->type == OPERATOR)
        {
            std::cout << "It's operator!" << std::endl;
            binary_list_add(binary, tok->data);
            binary_type_add(binary, OPERATOR);
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

void binary_destroy(Binary *binary)
{
    std::free(binary->data);
    std::free(binary->types);
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
                std::cout << "MUL" << std::endl;
                if (list->data[index + 1]->type == NUMBER)
                {
                    result *= list->data[index + 1]->data;
                    index++;
                }
                else
                {
                    std::cout << "Unexpected token at " << list->data[index + 1]->line << ':' << list->data[index + 1]->symbol << std::endl;
                    return -1;
                }
            }
            else if (list->data[index]->data == DIVIDE)
            {
                std::cout << "DIV" << std::endl;
                if (list->data[index + 1]->type == NUMBER)
                {
                    result /= list->data[index + 1]->data;
                    index++;
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

        index++;
    }

    std::cout << "Result: " << result << std::endl;

    binary_list_add(binary, result);
    binary_type_add(binary, NUMBER);

    return index;
};