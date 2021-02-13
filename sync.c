#include "header.h"
void sync_blockchain(struct nodes *node)
{
    int count_blocks_to_sync;
    struct nodes *current = node;
    struct blocks *current_head, *block_rm;
    char **bid_array = find_blocks_to_sync(current, &count_blocks_to_sync);
    while (current != NULL)
    {
        current_head = current->bidlist->head;
        if (current_head != NULL)
        {
            while (current_head != NULL)
            {
                block_rm = current_head;
                current_head = current_head->next;
                free(block_rm->bid);
                free(block_rm);
            }
            current->bidlist->head = NULL;
            current->bidlist_size = 0;
            for (int i = 0; i < count_blocks_to_sync; i++)
            {
                add_new_block(node, current->nid, my_strcpy1(bid_array[i]));
            }
        }
        else
        {
            for (int i = 0; i < count_blocks_to_sync; i++)
            {
                add_new_block(node, current->nid, my_strcpy1(bid_array[i]));
            }
        }
        current = current->next;
    }

    for (int i = 0; i < count_blocks_to_sync; ++i)
    {
        free(bid_array[i]);
    }
    free(bid_array);
}

char **find_blocks_to_sync(struct nodes *node, int *blocks_to_sync)
{
    char **blocks = malloc(100 * sizeof(char *));
    int count = 0;
    struct nodes *current = node;
    struct blocks *current_head;
    bool unique = true;
    while (current != NULL)
    {
        current_head = current->bidlist->head;
        while (current_head != NULL)
        {
            if (count == 0)
            {
                blocks[count] = my_strcpy1(current_head->bid);
                count++;
            }
            else
            {
                unique = true;
                for (int i = 0; i < count; i++)
                {
                    if (my_strcmp(blocks[i], current_head->bid) == true)
                    {
                        unique = false;
                    }
                }

                if (unique == true)
                {
                    blocks[count] = my_strcpy1(current_head->bid);
                    count++;
                }
            }
            current_head = current_head->next;
        }
        current = current->next;
    }
    *blocks_to_sync = count;
    return blocks;
}
