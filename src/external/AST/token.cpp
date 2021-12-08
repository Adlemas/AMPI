#include "token.h"

void token_list_destroy(TokenList *list)
{
    for (int i = 0; i < list->ptr; i++)
    {
        std::free(list->data[i]);
    }
    std::free(list->data);
};

Token *TokenList::getToken(TokenList *list, int pos)
{
    if (pos >= list->ptr)
    {
        Token *tok = (Token *)std::malloc(sizeof(Token));
        tok->type = UNDEFINED;
        tok->data = 0;
        tok->line = -1;
        tok->symbol = -1;
        tok->value = (char *)"";
        return tok;
    }
    else
        return list->data[pos];
}