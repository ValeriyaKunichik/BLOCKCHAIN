#include "header.h"
void add_block(const char *buff, struct nodes **masternode)
{
    char *bid = my_trunc_string(buff, 10);
    if (bid == NULL)
    {
        my_write_string(1, "Command not found\n");
    }
    else
    {
        const int bid_len = my_strlen(bid);
        const int nid = my_atoi(buff, 10 + bid_len + 1);

        if (nid < -1)
        {
            my_write_string(1, "Command not found\n");
            free(bid);
        }
        else if (nid == -1)
        {
            
            struct nodes *node = *masternode;
            while (node != NULL)
            {
               
                char *bid_cpy = my_strcpy1(bid);
                const int add_block_status = add_new_block(*masternode, node->nid, bid_cpy);
                if (add_block_status == 2)
                {
                    my_write_string(1, "This block already exists\n");
                    free(bid_cpy);
                    return;
                }
                if (add_block_status == 3)
                {
                    my_write_string(1, "Node doesn't exist\n");
                    free(bid_cpy);
                    return;
                }
                
                node = node->next;
            }
            free(bid);
        }
        else
        {
            
            const int add_block_status = add_new_block(*masternode, nid, bid);
            if (add_block_status == 2)
            {
                my_write_string(1, "This block already exists\n");
                free(bid);
                return;
            }
            if (add_block_status == 3)
            {
                my_write_string(1, "Node doesn't exist\n");
                free(bid);
                return;
            }
            
        }
    }
}

struct blocks *create_block(char *bid)
{
    struct blocks *new = (struct blocks *)malloc(sizeof(struct blocks));
    new->bid = bid;
    new->next = NULL;
    return new;
}

int add_new_block(struct nodes *node, int nid, char *bid)
{
    struct nodes *current = node;
    bool node_exist = false;

    while (current != NULL)
    {
        if (nid == current->nid)
        {
            struct blocks *new_block = create_block(bid);
            if (current->bidlist->head == NULL)
            {
                current->bidlist->head = new_block;
                current->bidlist->tail = current->bidlist->head;
                current->bidlist_size++;
            }
            else
            {
                struct blocks *current_block = current->bidlist->head;
                while (current_block != NULL)
                {
                    if (my_strcmp(current_block->bid, bid) == true)
                    {
                        free(new_block);
                        return 2;
                    }
                    else if (current_block->next == NULL)
                    {
                        break;
                    }
                    else
                    {
                        current_block = current_block->next;
                    }
                }
                current_block->next = new_block;
                current->bidlist->tail = new_block;
                current->bidlist_size++;
                
            }
            node_exist = true;
        }
        current = current->next;
    }
    if (node_exist == false)
    {   
        return 3;
    }
    else
    {   
        return 1;
    }
}
