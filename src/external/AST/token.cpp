#include "token.h"

void token_list_destroy(TokenList *list)
{
    for (int i = 0; i < list->ptr; i++)
    {
        std::free(list->data[i]);
    }
    std::free(list->data);
};