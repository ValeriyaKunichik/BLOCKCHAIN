#include "header.h"
void ls(struct nodes *node, const bool is_l)
{
    struct nodes *head = node;
    while (head != NULL)
    {
        my_write_integer(1, head->nid);
        if (is_l == true)
        {
            struct blocks *current_block = head->bidlist->head;
            while (current_block != NULL)
            {
                if (current_block == head->bidlist->head)
                {
                    my_write_string(1, ": ");
                }
                my_write_string(1, current_block->bid);
                if (current_block->next != NULL)
                {
                    my_write_string(1, ", ");
                }

                current_block = current_block->next;
            }
        }

        my_write_string(1, "\n");
        head = head->next;
    }
}

bool ls_l(const char *buff)
{
    if (my_strncmp(buff, "-l", 3, 2) == true)
    {
        return true;
    }
    return false;
}
