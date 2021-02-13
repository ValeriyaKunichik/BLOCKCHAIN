#include "header.h"
void add_node(const char *buff, struct nodes **masternode)
{
    const int nid = my_atoi(buff, 9);

    if (nid < 0)
    {
        my_write_string(1, "Command not found\n");
    }
    else
    {
        if (*masternode == NULL)
        {
            *masternode = create_node(nid);
        }
        else if (find_node(*masternode, nid) != NULL)
        {
            my_write_string(1, "This node already exists\n");
        }
        else
        {
            add_new_node(*masternode, nid);
        }
    }
}

struct nodes *create_node(int nid)
{
    struct nodes *new = (struct nodes *)malloc(sizeof(struct nodes));
    new->nid = nid;
    new->bidlist_size = 0;
    new->bidlist = (struct list_of_blocks *)malloc(sizeof(struct list_of_blocks));
    new->bidlist->head = NULL;
    new->bidlist->tail = NULL;
    new->next = NULL;

    return new;
}


void add_new_node(struct nodes *node, int nid)
{
    struct nodes *current = node;
    
    while (current != NULL && current->next != NULL)
    {
        current = current->next;
    }
    
    struct nodes *new = create_node(nid);
    current->next = new;
}
