#include "header.h"
void rm_block(const char *buff, struct nodes **masternode)
{
    char *bid = my_trunc_string(buff, 9);
    if (bid == NULL)
    {
        my_write_string(1, "Command not found\n");
    }
    else
    {
        const int bid_len = my_strlen(bid);
        const int str_len = my_strlen(buff) - 1;

        if ((bid_len + 9) != str_len)
        {
            my_write_string(1, "Command not found\n");
        }
        else if (find_block(*masternode, bid) == true)
        {
            rm_found_block(*masternode, bid);
        }
        else
        {
            my_write_string(1, "Block doesn't exist\n");
        }
        free(bid);
    }
}

void rm_found_block(struct nodes *node, char *bid)
{
    struct nodes *current = node;
    struct blocks *block_rm = NULL;
    struct blocks *current_block;
    struct blocks *previous;
    while (current != NULL)
    {
        int bidlist_size = current->bidlist_size;
        previous = current->bidlist->head;
        current_block = current->bidlist->head;
        block_rm = NULL;

        while (current_block != NULL)
        {
            if (my_strcmp(current_block->bid, bid) == true)
            {
                block_rm = current_block;
                if (bidlist_size == 1)
                {
                    current->bidlist->head = NULL;
                    current->bidlist_size = 0;
                }
                else if (previous == current_block)
                {
                    current->bidlist->head = current_block->next;
                    current->bidlist_size--;
                }
                else
                {
                    previous->next = current_block->next;
                    current->bidlist_size--;
                }
                break;
            }
            previous = current_block;
            current_block = current_block->next;
        }

        if (block_rm != NULL)
        {
            free(block_rm->bid);
            free(block_rm);
        }

        current = current->next;
    }
}

bool find_block(struct nodes *node, char *bid)
{
    struct nodes *current = node;
    struct blocks *current_block;
    while (current != NULL)
    {
        current_block = current->bidlist->head;
        while (current_block != NULL)
        {
            if (my_strcmp(current_block->bid, bid) == true)
            {
                return true;
            }
            current_block = current_block->next;
        }
        current = current->next;
    }
    return false;
}
