#include "header.h"
void rm_node(const char *buff, struct nodes **masternode)
{
    const int nid = my_atoi(buff, 8);
    if (nid < -1)
    {
        my_write_string(1, "Command not found\n");
    }
    else if (nid == -1)
    {
        rm_all_nodes(*masternode);
        *masternode = NULL;
    }
    else
    {
        struct nodes *nid_is_found = find_node(*masternode, nid);
        if (nid_is_found != NULL)
        {

            *masternode = rm_found_node(*masternode, nid);
        }
        else
        {
            my_write_string(1, "Node doesn't exist\n");
        }
    }
}

struct nodes *rm_found_node(struct nodes *masternode, int nid)
{
    struct nodes *head = masternode;
    struct nodes *current = masternode;
    struct nodes *previous = current;
    struct nodes *node_rm = NULL;
    struct blocks *tmp_block;
    while (current != NULL)
    {
        if (nid == current->nid)
        {
            node_rm = current;

            if (current == masternode)
            {
                head = current->next;
            }
            else
            {
                previous->next = current->next;
            }
            break;
        }
        previous = current;
        current = current->next;
    }

    if (node_rm != NULL)
    {
        while (node_rm->bidlist->head != NULL)
        {
            tmp_block = node_rm->bidlist->head;
            node_rm->bidlist->head = node_rm->bidlist->head->next;
            free(tmp_block->bid);
            free(tmp_block);
        }
        free(node_rm->bidlist);
        free(node_rm);
    }
    return head;
}

void rm_all_nodes(struct nodes *masternode)
{
    free_blockchain_node(masternode);
}
